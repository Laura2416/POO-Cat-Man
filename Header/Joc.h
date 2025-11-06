#ifndef JOC_H
#define JOC_H

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>

#include "Jucator.h"
#include "Fantoma.h"
#include "Harta.h"
#include "Energizer.h"


#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int _kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

int _getch() {
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif


class Joc {
private:
    Harta harta;
    Jucator jucator;
    std::vector<Fantoma> fantome;
    std::vector<Energizer> energize;
    std::chrono::steady_clock::time_point ultim_spawn;
    bool ruleaza;


    void verifica_coliziuni() {
        for (auto& f : fantome) {
            if (f.getX() == jucator.getX() && f.getY() == jucator.getY()) {
                if (!jucator.esteInvincibil()) {
                    std::cout << " Ai fost prins de o fantomă!\n";
                    jucator.pierdeViata();
                    if (jucator.getVieti() == 0) {
                        ruleaza = false;
                        std::cout << "\nGAME OVER!\n";
                        std::this_thread::sleep_for(std::chrono::seconds(10));
                    }
                }
            }
        }
    }

public:

    Joc() : ruleaza(true) {
        srand(static_cast<unsigned>(time(nullptr)));
    }


    bool porneste() {
        std::cout << "Alege o harta din 1 (mica), 2 (medie), 3 (mare): ";
        int opt;
        std::string numeFisier;
        int h=0, tries=0;
        while (!h && tries<=10 ) {
            std::cin >> opt;
            switch (opt) {
                case 1: {numeFisier = "../Header/harta1.txt"; h=1; break;}
                case 2: {numeFisier = "../Header/harta2.txt"; h=1; break;}
                case 3: {numeFisier = "../Header/harta3.txt"; h=1; break;}
                default: {std::cout<< "Alege una din hartile valabile! (1,2 sau 3): "; tries++;}
            }
            if (tries==10) std::cout<<"Mai ai o SINGURA incercare: ";
            else if (tries>10) {
                std::cout<<"Game Over n-ai putut alege o harta! \n";
                std::this_thread::sleep_for(std::chrono::seconds(2));
                std::cout<<"Pa!";
                std::this_thread::sleep_for(std::chrono::seconds(2));
                return false;
            }
        }
        if (!harta.incarca_din_fisier(numeFisier)) {
            std::cerr << "Eroare la încărcarea hărții.\n";
            return false;
        }

        jucator = Jucator(2, 2);
        fantome.clear();
        fantome.push_back(Fantoma(10, 3, "albastră"));
        fantome.push_back(Fantoma(15, 4, "roșie"));
        energize.clear();
        ultim_spawn = std::chrono::steady_clock::now();

        return true;
    }



    void afiseaza() {

        std::cout << "\033[H\033[J";

        std::vector<std::pair<int, int>> pozFantome;
        pozFantome.reserve(fantome.size());
        for (const auto& f : fantome)
            pozFantome.emplace_back(f.getX(), f.getY());

        std::vector<std::pair<int, int>> pozEnergize;
        pozEnergize.reserve(energize.size());
        for (const auto& e : energize)
            if (e.esteActiv()) pozEnergize.emplace_back(e.getX(), e.getY());

        harta.afiseaza(jucator.getX(), jucator.getY(), pozFantome, pozEnergize);
        std::cout << "\n Scor: " << jucator.getScor() << "    Vieti: " << jucator.getVieti() << "\n";
        if (jucator.esteInvincibil()) std::cout<< "INVINCIBIL\n";
        std::cout << "(W/A/S/D pentru miscare, Q pentru iesire)\n";
        std::cout.flush();
    }


    void actualizeaza() {
        if (_kbhit()) {
            char tasta = _getch();
            int nouX = jucator.getX();
            int nouY = jucator.getY();

            switch (tasta) {
                case 'w': nouY--; break;
                case 's': nouY++; break;
                case 'a': nouX--; break;
                case 'd': nouX++; break;
                case 'q': ruleaza = false; return;
                default: return;
            }

            auto acum=std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::seconds>(acum-ultim_spawn).count()>10) {
                Energizer e;
                e.setPozitieRandom(harta.getMatrice());
                energize.push_back(e);
                ultim_spawn=acum;
            }

            if (!harta.este_perete(nouX, nouY)) {
                jucator.setPozitie(nouX, nouY);
                if (harta.este_punct(nouX, nouY)) {
                    jucator.manancaPunct();
                    harta.sterge_punct(nouX, nouY);
                }
            }
            // După verificarea coliziunilor
            if (!harta.are_puncte_ramase()) {
                afiseaza();
                std::cout << "\n Ai castigat! Ai mancat toate punctele!\n";
                std::this_thread::sleep_for(std::chrono::seconds(10));
                ruleaza = false;
                return;
            }

        }

        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
        for (auto& f : fantome)
            f.muta_random(harta);
        //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! vreau sa le fac sa se mute mai bine
        verifica_coliziuni();
        for (auto& e : energize){
            if (e.esteActiv() && e.getX()==jucator.getX() && e.getY()==jucator.getY()) {
                e.dezactiveaza();
                jucator.activeazaInvincibilitate();
                jucator.adaugaScor(50);
                std::cout << "Ai colectat un energizer! Esti invincibil!\n";
            }
        }
    }


    void ruleaza_joc() {
        if (!porneste()) return;

        while (ruleaza) {
            afiseaza();
            actualizeaza();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }


    friend std::ostream& operator<<(std::ostream& os, const Joc& j) {
        os << "Joc cu " << j.fantome.size() << " fantome și un jucător.\n";
        os << j.harta;
        return os;
    }
};

#endif
