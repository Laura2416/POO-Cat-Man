
#ifndef OOP_JOC_H
#define OOP_JOC_H

#include <iostream>
#include <vector>
#include <conio.h>
#include <cstdlib>
#include <ctime>

#include "Jucator.h"
#include "Fantoma.h"
#include "Harta.h"

class Joc {
    Harta harta;
    Jucator jucator;
    std::vector<Fantoma> fantome;
    bool ruleaza;

    public:
        Joc () {
            ruleaza = true;
            srand(static_cast<unsigned>(time(nullptr)));
        }

    bool porneste() {
            if (!harta.incarca_din_fisier("../Header/harta.txt")) {
                std::cerr << "Errore file. \n";
                return false;
            }
            jucator= Jucator(2, 2);
            fantome.push_back(Fantoma(10, 3, "albastra"));
            fantome.push_back(Fantoma(15, 4, "rosie"));

            return true;
        }

    void afiseaza() {
            system("cls");
            harta.afiseaza();

            std::cout << "\nJucator: (" << jucator.getX() << ", " << jucator.getY() << ")"
                  << "  Scor: " << jucator.getScor()
                  << "  Vieti: " << jucator.getVieti() << "\n";
            for (size_t i=0; i<fantome.size(); i++) {
                std::cout << "Fantoma " << i + 1 << ": ("
                      << fantome[i].getX() << ", " << fantome[i].getY() << ")\n";
            }
        }

    void verifica_coliziuni() {
            for (auto& f: fantome) {
                if (f.getX()==jucator.getX() && f.getY()==jucator.getY()) {
                    std::cout << "Ai fost prins de o fantoma!\n";
                    jucator.pierdeViata();
                    if (jucator.getVieti()==0) {
                        ruleaza = false;
                        std::cout<< "Game Over!\n";
                    }
                }
            }
        }
    void actualizeaza() {
            if (_kbhit()) {
                char tasta= _getch();
                switch (tasta) {
                    case 'w': jucator.setDirectie('U'); break;
                    case 's': jucator.setDirectie('D'); break;
                    case 'a': jucator.setDirectie('L'); break;
                    case 'd': jucator.setDirectie('R'); break;
                    case 'q': ruleaza = false; return;
                }

                int nouX=jucator.getX();
                int nouY=jucator.getY();
                switch (tasta) {
                    case 'w': nouY--; break;
                    case 's': nouY++; break;
                    case 'a': nouX--; break;
                    case 'd': nouX++; break;
                }

                if (!harta.este_perete(nouX,nouY)){ jucator.setPozitie(nouX,nouY);
                    if (harta.este_punct(nouX,nouY)) {
                        jucator.manancaPunct();
                        harta.sterge_punct(nouX,nouY);
                    }
                }
            }
            for (auto& f: fantome)
                f.muta_random();

            verifica_coliziuni();
        }

    void ruleaza_joc() {
            if (!porneste()) return;

            while (ruleaza) {
                afiseaza();
                actualizeaza();
                _sleep(300);
            }
        }
};

#endif //OOP_JOC_H