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
    int getDurata() const {return durata;}

    void dezactiveaza() {
        activ=false;
    }

    void setPozitieRandom(const std::vector<std::string>& matrice) {
        int inaltime=matrice.size();
        int latime=matrice[0].size();
        int nouX, nouY;
        do {
            nouX=rand()%latime;
            nouY=rand()%inaltime;
        } while (matrice[nouX][nouY]=='#');
        x=nouX;
        y=nouY;
        activ=true;
    }
    friend std::ostream& operator<<(std::ostream& os, const Energizer& e) {
        if (e.activ)
            os<< "Activ";
            else os<< "Inactiv";
        return os;
    }

};


#endif //OOP_ENERGIZER_H