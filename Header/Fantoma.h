//
// Created by WIN on 11/2/2025.
//

#ifndef OOP_FANTOMA_H
#define OOP_FANTOMA_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

class Fantoma {
    int x,y;
    int viteza;
    std::string culoare;
    char directie; // 'U'=sus 'D'=jos 'L'=left 'R'=right

    public:
     Fantoma() {
     x=y=0;
     viteza=1;
     culoare="rosie";
     directie='U';
    }

    Fantoma(int xInit, int yInit, std::string c) {
         x=xInit;
         y=yInit;
         viteza=1;
         culoare=c;
         directie='U';
     }

    int getX() const {return x;}
    int getY() const {return y;}
    std::string getCuloare() const {return culoare;}

    void setPozitie(int nouX, int nouY) {
         x=nouX;
         y=nouY;
     }

    void muta_random() {
         int r= rand()%4;
         switch (r) {
             case 0:
                 y-= viteza;
                 directie='U';
                 break;
             case 1:
                 y+= viteza;
                 directie='D';
                 break;
             case 2:
                 y+= viteza;
                 directie='R';
                 break;
             case 3:
                 y-=viteza;
                 directie='L';
                 break;
         }
     }

    void afiseaza() const {
         std::cout << "Fantoma (" << culoare << ") se afla la (" << x<< "," << y << ") si se deplaseaza spre";
         switch (directie) {
             case 'U': std::cout << "nord"; break;
                 case 'D': std::cout << "sud"; break;
                 case 'R': std::cout << "est"; break;
                 case 'L': std::cout << "vest"; break;
         }
         std::cout <<".\n";

     }
};

#endif //OOP_FANTOMA_H