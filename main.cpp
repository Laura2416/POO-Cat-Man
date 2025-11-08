#include <iostream>
#include "Header/Joc.h"
#include "Header/Meniu.h"
#include "Header/Harta.h"


int main() {

srand(time(nullptr));

    Meniu meniu;
    Joc joc;
    Harta harta;

    bool ruleaza=true;

    while (ruleaza) {
        meniu.afiseaza();
        int opt=meniu.citesteOpt();
        switch (opt) {
            case 1: {
                if (joc.porneste()) joc.ruleaza_joc();
                break;
            }
                case 2: {
                std::cout<<"Uite hartile:\n";
                harta.veziHarti();
                break;
            }
                case 3: {
                meniu.afiseazaInstructiuni();
                break;
            }
                case 4: {
                std::cout<<"Paaaaaaa!\n";
                ruleaza=false;
                break;
            }
        }
    }

    return 0;
}
