

#ifndef OOP_MENIU_H
#define OOP_MENIU_H

#include <iostream>
#include <string>
#include <limits>

class Meniu {
    int optSelectata;

    public:
    Meniu() {
        optSelectata=0;
    }

    ~Meniu() = default;

    void afiseaza() const {
        std::cout<<"\n      MENIU PRINCIPAL      \n";
        std::cout<<"1. Joaca jocul\n";
        std::cout<<"2. Vizualizeaza hartile\n";
        std::cout<<"3. Instructiuni\n";
        std::cout<<"4. Iesire\n";
        std::cout<<"------------------------------\n";
        std::cout<<"Alege o optiune: ";
    }

    int citesteOpt() {
        int opt;
        std::cin>>opt;

        while (std::cin.fail()|| opt<1 || opt>4) {
            std::cout<<"Alege o optiune valida: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin>>opt;
        }

        optSelectata=opt;
        return opt;
    }

    void afiseazaInstructiuni() const {
        std::cout<<"\n   INSTRUCTIUNI     \n";
        std::cout<<"Scopul jocului este sa mananci toate punctele (.), fara sa fii prins de fantome.\n";
        std::cout<<"Pentru a te misca, foloseste tastele W/A/S/D\n";
        std::cout<<"Cand apare simbolul $, inseamna ca a aparut un energizer, pe care daca il vei manca, iti va oferi puncte in plus si invincibilitate 3 secunde\n";
        std::cout<<"Fereste-te de fantome! (F) Ai 3 vieti la dispozitie, tine de ele!\n";
        std::cout<<"In momentul in care nu mai sunt puncte pe harta, ai castigat!\n";
        std::cout<<"Apasa ENTER pentru a reveni la meniu...";
        std::cin.ignore();
        std::cin.get();
    }

    [[maybe_unused]] getOpt() const {return optSelectata;}
};
#endif //OOP_MENIU_H