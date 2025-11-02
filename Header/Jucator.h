#ifndef OOP_JUCATOR_H
#define OOP_JUCATOR_H

#include <iostream>
#include <string>

class Jucator {
    int x,y;
    int viteza, vieti, scor;
    char directie; // 'U'=sus 'D'=jos 'L'=left 'R'=right

public:
    Jucator() {
        x=y=0;
        viteza=1;
        vieti=3;
        scor=0;
        directie='R';
    }

    Jucator (int xInit, int yInit) {
        x=xInit;
        y=yInit;
        viteza=1;
        vieti=3;
        scor=0;
        directie='R';
    }

    int getX() const { return x; }
    int getY() const { return y; }
    int getVieti() const { return vieti; }
    int getScor() const { return scor; }

    void setPozitie(int nouX, int nouY) {
        x=nouX;
        y=nouY;
    }

    void setDirectie (char d) {
        if (d=='U' || d=='D' || d=='L' || d=='R')
            directie=d;
    }
    void muta() {
        switch (directie) {
            case 'U': y-=viteza; break;
            case 'D': y+=viteza; break;
            case 'L': y-=viteza; break;
            case 'R': y+=viteza; break;
        }
    }

    void manancaPunct() {
        scor+=10;
    }

    void pierdeViata() {
        vieti--;
        if (vieti<0) vieti=0;
    }
    void afiseaza() const {
        std::cout << "Jucatorul se afla la (" << x << ", " << y << ")" << ")" << "cu "
<<vieti << "cieti si scor" << scor << ".\n";
    }
};

#endif //OOP_JUCATOR_H
