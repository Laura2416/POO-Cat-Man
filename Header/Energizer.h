//
// Created by WIN on 11/6/2025.
//

#ifndef OOP_ENERGIZER_H
#define OOP_ENERGIZER_H


#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <string>
#include <fstream>


class Energizer {
    int x,y;
    int durata;
    bool activ;

    public:
    Energizer() {
        x=y=0;
        activ=false;
        durata=5;
    }
    Energizer(int xNou, int yNou, int durataNoua) {
        x=xNou;
        y=yNou;
        activ=true;
        durata=durataNoua;
    }
    Energizer& operator=(const Energizer& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
            activ = other.activ;
            durata = other.durata;
        }
        std::cout<<"Operator = apelat pentru energizer\n";
        return *this;
    }
    ~Energizer() {
        std::cout<<"Destructor apelat\n";
    }
    int getX() const {return x;}
    int getY() const {return y;}
    bool esteActiv() const{ return activ;}
    //int getDurata() const {return durata;}

    void dezactiveaza() {
        activ=false;
    }

    void setPozitieRandom(const std::vector<std::string>& matrice) {
        std::ofstream log("../debug/debug.txt", std::ios::app);
        //log << "Pornit seteazaPozitieRandom()" << std::endl;
        //log.close();
        if (matrice.empty() || matrice[0].empty()) {
            std::cerr << "[Eroare] Harta goala — nu pot genera energizer.\n";
            return;
        }
        int inaltime=matrice.size();
        int latime=matrice[0].size();
        int nouX, nouY;
        for (const auto& linie : matrice) {
            if ((int)linie.size() != latime) {
                std::cerr << "[Eroare] Harta invalida: liniile au lungimi diferite.\n";
                return;
            }
        }
        int incercari=0;
        const int MAX_INCERCARI=10000;
        while (true) {
            nouX=rand()%latime;
            nouY=rand()%inaltime;
            //std::ofstream log("debug.txt", std::ios::app);
            //log << "nouX=" << nouX << " nouY=" << nouY
            //    << " matrice[" << nouY << "].size()=" << matrice[nouY].size()
            //    << std::endl;

            //log.close();

            if (nouY>=0 && nouY<inaltime && nouX>=0 && nouX<(int)matrice[nouY].size() && matrice[nouY][nouX]!='#') break;
            if (++incercari==MAX_INCERCARI) {
                std::cerr<<"Nu s-a putut gasi o pozitie libera pt energizer";
                return;
            }
        }
        x=nouX;
        y=nouY;
        activ=true;
    }
    friend std::ostream& operator<<(std::ostream& os, const Energizer& e) {
        os << "Energizer (" << e.x << "," << e.y << ") "
           << (e.activ ? "Activ" : "Inactiv")
           << " | durata=" << e.durata << "s";
        return os;
    }

};


#endif //OOP_ENERGIZER_H