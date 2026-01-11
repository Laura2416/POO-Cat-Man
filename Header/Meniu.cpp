#include "Meniu.h"
#include <limits>

Meniu::Meniu() : optSelectata(0), fantomeSetting(0) {}

void Meniu::afiseaza() const {
    std::cout << "\n      MENIU PRINCIPAL      \n";
    std::cout << "1. Joaca jocul\n";
    std::cout << "2. Vizualizeaza hartile\n";
    std::cout << "3. Instructiuni\n";
    std::cout << "4. Fantome (Default sau 1-4)\n";
    std::cout << "5. Iesire\n";
    std::cout << "------------------------------\n";
    std::cout << "(Setare curenta fantome: ";
    if (fantomeSetting == 0) std::cout << "Default"; else std::cout << fantomeSetting;
    std::cout << ")\n";
    std::cout << "Alege o optiune: ";
}

int Meniu::citesteOpt() {
    int opt;
    std::cin >> opt;

    while (std::cin.fail() || opt < 1 || opt > 5) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Alege o optiune valida (1-5): ";
        std::cin >> opt;
    }

    optSelectata = opt;
    if (optSelectata == 4) {
        selecteazaFantome();
        // intoarcem la meniu principal: returnam o valoare care nu lanseaza joc/iesire
        return 0;
    }
    return opt;
}

void Meniu::afiseazaSetariFantome() const {
    std::cout << "\n   SETARI FANTOME     \n";
    std::cout << "0. Default (mica=2, medie=3, mare=4)\n";
    std::cout << "1. 1 fantoma\n";
    std::cout << "2. 2 fantome\n";
    std::cout << "3. 3 fantome\n";
    std::cout << "4. 4 fantome\n";
    std::cout << "Alege: ";
}

void Meniu::selecteazaFantome() {
    afiseazaSetariFantome();
    int x; std::cin >> x;
    while (std::cin.fail() || x < 0 || x > 4) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Alege o optiune valida (0–4): ";
        std::cin >> x;
    }
    fantomeSetting = x;
}

int Meniu::getFantomeSetting() const { return fantomeSetting; }

void Meniu::afiseazaInstructiuni() const {
    std::cout << "\n   INSTRUCTIUNI     \n";
    std::cout << "Scopul jocului este sa mananci toate punctele (.), fara sa fii prins de fantome.\n";
    std::cout << "Castigi cand nu mai sunt puncte pe harta.\n";
    std::cout << "Pentru a te misca, foloseste tastele W/A/S/D\n";
    std::cout << "Simbolul $ apare aleator pe harta (energizer): daca il mananci,\n";
    std::cout << "primesti puncte bonus si 3 secunde de invincibilitate.\n";
    std::cout << "Fereste-te de fantome! (F) Ai 3 vieti la dispozitie.\n";
    std::cout << "\nApasa ENTER pentru a reveni la meniu...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

std::ostream& operator<<(std::ostream& os, const Meniu& m) {
    os << "Meniu principal (ultima optiune selectata: ";
    if (m.optSelectata == 0) os << "niciuna";
    else os << m.optSelectata;
    os << ", fantome=" << (m.fantomeSetting==0?std::string("Default"):std::to_string(m.fantomeSetting)) << ")";
    return os;
}
