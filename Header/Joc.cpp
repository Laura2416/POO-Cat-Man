#include "Joc.h"
#include "Fantoma.h"
#include "Energizer.h"
#include "Punct.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <algorithm>
#include <cctype>
#include <cstdlib>

#ifdef _WIN32
#include <conio.h>
#else
#include <unistd.h>
#endif

Joc::Joc() : jucator(nullptr), ruleaza(true), ultimaDirectie(' ') {}

void Joc::porneste()
{
    while (ruleaza)
    {
        meniu.afiseaza();
        int opt = meniu.citesteOpt();

        if (opt == 0) continue; // revenit din submeniu

        switch (opt)
        {
        case 1:
            if (pornesteJoc())
                ruleazaJoc();
            break;

        case 2:
            veziHarti();
            break;

        case 3:
            meniu.afiseazaInstructiuni();
            break;

        case 5:
            ruleaza = false;
            break;
        default:
            break;
        }
    }
}

bool Joc::pornesteJoc()
{
    std::cout << "Alege harta (1-3): ";
    int opt;
    std::cin >> opt;

    std::string fisier;
    if (opt == 1) { fisier = "maps/harta1.txt"; selectedMapIndex = 1; }
    else if (opt == 2) { fisier = "maps/harta2.txt"; selectedMapIndex = 2; }
    else if (opt == 3) { fisier = "maps/harta3.txt"; selectedMapIndex = 3; }
    else {
        std::cout << "Optiune invalida!\n";
        return false;
    }

    if (!harta.incarca(fisier))
    {
        std::cout << "Nu s-a putut incarca harta!\n";
        return false;
    }

    entitati.clear();

    // jucatotul apare in primu loc liber
    int sx = 1, sy = 1;
    for (int y = 1; y < harta.getInaltime(); ++y) {
        bool found = false;
        for (int x = 1; x < harta.getLatime(); ++x) {
            if (!harta.estePerete(x,y)) { sx = x; sy = y; found = true; break; }
        }
        if (found) break;
    }
    auto j = std::make_unique<Jucator>(sx, sy);
    jucator = j.get();
    entitati.push_back(std::move(j));

    for (int y = 0; y < harta.getInaltime(); y++)
        for (int x = 0; x < harta.getLatime(); x++) {
            if (harta.at(x, y) == '.')
                entitati.push_back(std::make_unique<Punct>(x, y));
        }

    // fantome: numar in functie de marimea hartii sau override din meniu
    int defaultGhosts = (selectedMapIndex==1?2:(selectedMapIndex==2?3:4));
    int set = meniu.getFantomeSetting();
    int ghosts = (set==0 ? defaultGhosts : set);

    // alegem personalitati distincte pentru fantome
    std::vector<Fantoma::Personalitate> all = {
        Fantoma::Personalitate::Chaser,
        Fantoma::Personalitate::Runner,
        Fantoma::Personalitate::Stalker,
        Fantoma::Personalitate::Random
    };
    for (size_t i=0;i<all.size();++i){
        size_t jdx = (size_t)(rand()%all.size());
        std::swap(all[i], all[jdx]);
    }
    ghosts = std::max(1, std::min((int)all.size(), ghosts));

    // functia pentru a gasi un spawn liber
    auto findFree = [&](int& ox, int& oy){
        for (int tries=0; tries<200; ++tries){
            int x = 1 + rand() % std::max(1, harta.getLatime()-2);
            int y = 1 + rand() % std::max(1, harta.getInaltime()-2);
            if (harta.estePerete(x,y)) continue;
            bool blocked = false;
            if (x==jucator->getX() && y==jucator->getY()) blocked=true;
            if (!blocked){
                for (const auto& e : entitati){
                    if (dynamic_cast<Fantoma*>(e.get())){
                        if (e->getX()==x && e->getY()==y) { blocked=true; break; }
                    }
                }
            }
            if (!blocked){ ox=x; oy=y; return true; }
        }
        return false;
    };

    for (int i=0;i<ghosts;i++){
        int gx = sx, gy = sy;
        findFree(gx, gy);
        entitati.push_back(std::make_unique<Fantoma>(gx, gy, all[i], jucator));
    }
    ultimaDirectie = ' ';
    scheduleNextEnergizer();

    return true;
}

void Joc::scheduleNextEnergizer() {
    int span = spawnMinMs + (rand() % std::max(1, spawnMaxMs - spawnMinMs + 1));
    nextEnergizerSpawn = std::chrono::steady_clock::now() + std::chrono::milliseconds(span);
}

int Joc::countActivePuncte() const {
    int cnt = 0;
    for (const auto& e : entitati) {
        if (auto p = dynamic_cast<Punct*>(e.get())) if (p->esteActiv()) cnt++;
    }
    return cnt;
}

int Joc::countActiveEnergizers() const {
    int cnt = 0;
    for (const auto& e : entitati) {
        if (auto en = dynamic_cast<Energizer*>(e.get())) if (en->esteActiv()) cnt++;
    }
    return cnt;
}

bool Joc::isOccupiedByBlocking(int x, int y) const {
    if (harta.estePerete(x,y)) return true;
    if (jucator && jucator->getX()==x && jucator->getY()==y) return true;
    for (const auto& e : entitati) {
        if (auto f = dynamic_cast<Fantoma*>(e.get())) {
            if (f->getX()==x && f->getY()==y) return true;
        }
        if (auto en = dynamic_cast<Energizer*>(e.get())) {
            if (en->esteActiv() && en->getX()==x && en->getY()==y) return true;
        }
    }
    return false;
}

void Joc::maybeSpawnEnergizer() {
    auto now = std::chrono::steady_clock::now();
    if (now < nextEnergizerSpawn) return;
    if (countActiveEnergizers() >= maxActiveEnergizers) return;

    // cautam un loc liber random
    for (int tries=0; tries<300; ++tries) {
        int x = 1 + rand() % std::max(1, harta.getLatime()-2);
        int y = 1 + rand() % std::max(1, harta.getInaltime()-2);
        if (!isOccupiedByBlocking(x,y)) {
            entitati.push_back(std::make_unique<Energizer>(x, y));
            break;
        }
    }
    scheduleNextEnergizer();
}

void Joc::ruleazaJoc()
{
    bool inJoc = true;

    // viteza jocului (fps simplu) — marim delay-ul pentru a incetini jocul
    const int millisPerTick = 180;


    //la partea asta am avut nevoie de ajutor, nu siam cum sa fac sa mute pozitia fara sa apas si pe enter
    while (inJoc)
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        // citire non-blocanta si miscare pe eveniment (1 apasare = 1 pas)
#ifdef _WIN32
        if (_kbhit()) {
            int ch = _getch();
            if (ch == 'q' || ch == 'Q') break;
            if (ch=='w'||ch=='a'||ch=='s'||ch=='d'||ch=='W'||ch=='A'||ch=='S'||ch=='D') {
                char dir = static_cast<char>(tolower(ch));
                jucator->muta(dir, harta);
            }
        }
#else
#endif

        // spawn energizer daca e momentul
        maybeSpawnEnergizer();

        // update entitati (fantome, etc.) — mai lent pentru fantome
        static int tick = 0;
        tick++;
        for (auto& e : entitati) {
            if (auto f = dynamic_cast<Fantoma*>(e.get())) {
                // misca fantoma o data la 2 tick-uri
                if (tick % 2 == 0) f->update(harta);
            } else {
                e->update(harta);
            }
        }

        //colectare puncte, energizer, coliziuni
        for (auto& e : entitati)
            e->interact(*jucator);

        // sterge puncte/energizer colectate
        entitati.erase(
            std::remove_if(entitati.begin(), entitati.end(), [](const std::unique_ptr<Entitate>& e){
                if (auto p = dynamic_cast<Punct*>(e.get())) return !p->esteActiv();
                if (auto en = dynamic_cast<Energizer*>(e.get())) return !en->esteActiv();
                return false;
            }),
            entitati.end()
        );

        afiseaza();

        // win condition: fara puncte ramase
        if (countActivePuncte() == 0) {
            std::cout << "\nAI CASTIGAT! Nu mai sunt puncte pe harta.\n";
#ifdef _WIN32
            system("pause");
#else
            std::cout << "\nApasa Enter...";
            std::cin.ignore();
            std::cin.get();
#endif
            break;
        }

        if (jucator->getVieti() == 0)
        {
            std::cout << "\nGAME OVER\n";
#ifdef _WIN32
            system("pause");
#else
            std::cout << "\nApasa Enter...";
            std::cin.ignore();
            std::cin.get();
#endif
            break;
        }

        // asteapta urmatorul tick
        std::this_thread::sleep_for(std::chrono::milliseconds(millisPerTick));
    }
}

void Joc::afiseaza()
{
    std::vector<std::pair<int,int>> fantome;
    std::vector<std::pair<int,int>> energizere;
    std::vector<std::pair<int,int>> puncte;

    for (const auto& e : entitati)
    {
        if (auto f = dynamic_cast<Fantoma*>(e.get())) {
            (void)f;
            fantome.emplace_back(e->getX(), e->getY());
            continue;
        }
        if (auto en = dynamic_cast<Energizer*>(e.get())) {
            if (en->esteActiv()) energizere.emplace_back(en->getX(), en->getY());
            continue;
        }
        if (auto p = dynamic_cast<Punct*>(e.get())) {
            if (p->esteActiv()) puncte.emplace_back(p->getX(), p->getY());
            continue;
        }
    }

    harta.afiseaza(jucator->getX(), jucator->getY(), fantome, energizere, puncte);

    std::cout << "\nScor: " << jucator->getScor()
              << "  Vieti: " << jucator->getVieti() << "\n";

    if (jucator->esteInvincibil())
        std::cout << "INVINCIBIL\n";
}

void Joc::veziHarti()
{
        std::cout << "\n1. Harta mica\n";
        std::cout << "2. Harta medie\n";
        std::cout << "3. Harta mare\n";
        std::cout << "Alege: ";

        int opt;
        std::cin >> opt;

        std::string fisier;
        if (opt == 1) fisier = "maps/harta1.txt";
        else if (opt == 2) fisier = "maps/harta2.txt";
        else if (opt == 3) fisier = "maps/harta3.txt";
        else {
            std::cout << "Optiune invalida\n";
            return;
        }

        Harta h;
        if (!h.incarca(fisier)) {
            std::cout << "Nu s-a putut incarca harta\n";
            return;
        }

        std::cout << "\n--- Harta ---\n";
        std::cout << h;

        std::cout << "\nApasa ENTER...";
        std::cin.ignore();
        std::cin.get();

}
