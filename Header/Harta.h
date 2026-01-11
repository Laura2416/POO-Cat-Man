#pragma once
#include <vector>
#include <string>
#include <iostream>

class Harta {
    std::vector<std::string> grid;
    int h, w;

public:
    Harta();

    bool incarca(const std::string& fisier);

    bool estePerete(int x, int y) const;
    bool estePunct(int x, int y) const;

    int getInaltime() const;
    int getLatime() const;
    char at(int x, int y) const;

    void afiseaza(int px, int py,
                  const std::vector<std::pair<int,int>>& fantome,
                  const std::vector<std::pair<int,int>>& energizere,
                  const std::vector<std::pair<int,int>>& puncte) const;

    friend std::ostream& operator<<(std::ostream& os, const Harta& h);

};
