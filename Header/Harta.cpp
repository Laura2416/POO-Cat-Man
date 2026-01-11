#include "Harta.h"
#include <fstream>

Harta::Harta() : h(0), w(0) {}

bool Harta::incarca(const std::string& fisier) {
    std::ifstream fin(fisier);
    if (!fin) return false;

    grid.clear();
    std::string line;
    while (std::getline(fin, line))
        grid.push_back(line);

    h = grid.size();
    w = h ? grid[0].size() : 0;
    return true;
}

bool Harta::estePerete(int x, int y) const {
    if (x < 0 || y < 0 || y >= h || x >= w) return true;
    return grid[y][x] == '#';
}

bool Harta::estePunct(int x, int y) const {
    if (x < 0 || y < 0 || y >= h || x >= w) return false;
    return grid[y][x] == '.';
}

int Harta::getInaltime() const { return h; }
int Harta::getLatime() const { return w; }
char Harta::at(int x, int y) const { return grid[y][x]; }

void Harta::afiseaza(int px, int py,
    const std::vector<std::pair<int,int>>& fantome,
    const std::vector<std::pair<int,int>>& energizere,
    const std::vector<std::pair<int,int>>& puncte) const {

    for (int y=0; y<h; y++) {
        for (int x=0; x<w; x++) {
            char outChar = ' ';

            // prioritate: Jucator > Fantoma > Energizer > Punct > baza
            if (x==px && y==py) {
                outChar = 'P';
            } else {
                bool isF = false, isE = false, isP = false;
                for (const auto& f: fantome) { if (f.first==x && f.second==y) { isF=true; break; } }
                if (isF) {
                    outChar = 'F';
                } else {
                    for (const auto& e: energizere) { if (e.first==x && e.second==y) { isE=true; break; } }
                    if (isE) {
                        outChar = '$';
                    } else {
                        for (const auto& p: puncte) { if (p.first==x && p.second==y) { isP=true; break; } }
                        if (isP) {
                            outChar = '.';
                        } else {
                            char base = grid[y][x];
                            if (base == '.' || base == '$') base = ' ';
                            outChar = base;
                        }
                    }
                }
            }
            std::cout << outChar;
        }
        std::cout<<"\n";
    }
}
    std::ostream& operator<<(std::ostream& os, const Harta& h) {
        for (int y = 0; y < h.getInaltime(); y++) {
        for (int x = 0; x < h.getLatime(); x++) {
            os << h.at(x, y);
        }
        os << '\n';
         }
        return os;
}
