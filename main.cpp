#include <iostream>
#include "Header/Jucator.h"
#include "Header/Fantoma.h"
#include "Header/Harta.h"

int main() {
    Jucator pacman(2, 3);  // pozitie initiala (2,3)

    pacman.afiseaza();

    pacman.setDirectie('R'); // mutare spre dreapta
    pacman.muta();
    pacman.afiseaza();

    pacman.manancaPunct();
    pacman.afiseaza();

    pacman.pierdeViata();
    pacman.afiseaza();

    srand(time(0)); // initializare generator aleator

    Fantoma f1(5, 5, "albastra");

    for (int i = 0; i < 5; ++i) {
        f1.muta_random();
        f1.afiseaza();
    }
    Harta h;
    if (!h.incarca_din_fisier("../Header/harta.txt")) {
        std::cerr << "Nu s-a putut incarca harta.\n";
        return 1;
    }

    std::cout << "=== Harta initiala ===\n";
    h.afiseaza();

    int x = 2, y = 1;
    if (h.este_punct(x, y)) {
        std::cout << "Exista un punct la (" << x << ", " << y << ")! Il mancam...\n";
        h.sterge_punct(x, y);
    }

    std::cout << "\n=== Harta dupa mancare ===\n";
    h.afiseaza();


    return 0;
}
