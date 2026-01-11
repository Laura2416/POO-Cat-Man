#ifndef MENIU_H
#define MENIU_H

#include <iostream>
#include <string>

class Meniu {
    int optSelectata;
    int fantomeSetting; // 0 = Default, 1..4 = numar fix

public:
    Meniu();
    ~Meniu() = default;

    void afiseaza() const;
    int citesteOpt();
    // submeniu pentru alegerea numarului de fantome
    void afiseazaSetariFantome() const;
    void selecteazaFantome();
    int getFantomeSetting() const;
    void afiseazaInstructiuni() const;

    friend std::ostream& operator<<(std::ostream& os, const Meniu& m);
};

#endif
