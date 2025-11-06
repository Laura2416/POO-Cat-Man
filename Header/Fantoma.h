#ifndef FANTOMA_H
#define FANTOMA_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Harta.h"

class Fantoma {
private:
    int x, y;
    std::string culoare;

public:
    Fantoma(int x = 0, int y = 0, const std::string& c = "albastră")
        : x(x), y(y), culoare(c) {}

    int getX() const { return x; }
    int getY() const { return y; }
    std::string getCuloare() const { return culoare; }

    // Mută fantoma aleator, dar doar dacă nu e perete
    void muta_random(const Harta& harta) {
        int directie = rand() % 4;
        int nouX = x, nouY = y;

        switch (directie) {
            case 0: nouY--; break; // sus
            case 1: nouY++; break; // jos
            case 2: nouX--; break; // stânga
            case 3: nouX++; break; // dreapta
        }

        if (!harta.este_perete(nouX, nouY)) {
            x = nouX;
            y = nouY;
        }
    }

    friend std::ostream& operator<<(std::ostream& os, const Fantoma& f) {
        os << "Fantoma (" << f.culoare << ") la (" << f.x << ", " << f.y << ")";
        return os;
    }
};

#endif
