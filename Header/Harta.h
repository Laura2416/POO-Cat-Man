#ifndef OOP_HARTA_H
#define OOP_HARTA_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class Harta {
    std::vector<std::string> matrice;
    int inaltime, latime;

    public:
        Harta() {
            latime = 0;
            inaltime = 0;
        }
    bool incarca_din_fisier(const std::string& numeFisier) {
            std::ifstream fin(numeFisier);
            if (!fin.is_open()) {
                std::cerr << "Errore apertura file" << numeFisier << std::endl;
                return false;
            }
            std::string line;
            matrice.clear();
            while (std::getline(fin, line)) {
                matrice.push_back(line);
            }
            fin.close();

            if (!matrice.empty()) {
                inaltime=matrice.size();
                latime=matrice[0].size();
            }
            return true;
        }

    void afiseaza() const {
            for (const auto& linie:matrice)
                std::cout << linie << "\n";
        }

    bool este_perete(int x, int y) const {
            if (y<0 || y>=inaltime || x<0 || x>=latime) return true;
            return matrice[x][y]=='#';
        }

    bool este_punct(int x, int y) const {
            if (y<0 || y>=inaltime || x<0 || x>=latime) return false;
            return matrice[x][y]== '.';
        }

    void sterge_punct (int x, int y) {
            if (y>=0 && y<inaltime && x>=0 && x<latime)
                if (matrice[y][x]=='.') matrice[y][x]=' ';
        }
    int getLatime() const {return latime;}
    int getInaltime() const {return inaltime;}
};

#endif //OOP_HARTA_H