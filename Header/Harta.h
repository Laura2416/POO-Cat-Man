#ifndef OOP_HARTA_H
#define OOP_HARTA_H

#include <iostream>
#include <vector>
#include <fstream>
#include <string>

class Harta {
    std::vector<std::string> matrice;
    int inaltime, latime;
    bool este_in_limite(int x, int y) const {
        return (y >= 0 && y < inaltime && x >= 0 && x < latime);
    }

    public:
       Harta() : inaltime(0), latime(0) {}


    explicit Harta(const std::string& fisier) {
        incarca_din_fisier(fisier);
    }


    Harta(const Harta& other)
        : matrice(other.matrice), inaltime(other.inaltime), latime(other.latime) {
        std::cout << "[DEBUG] Constructor de copiere apelat pentru Harta\n";
    }


    Harta& operator=(const Harta& other) {
        if (this != &other) {
            matrice = other.matrice;
            inaltime = other.inaltime;
            latime = other.latime;
        }
        std::cout << "[DEBUG] Operator= apelat pentru Harta\n";
        return *this;
    }


    ~Harta() {
        std::cout << "[DEBUG] Destructor apelat pentru Harta\n";
        matrice.clear();
    }


    bool incarca_din_fisier(const std::string& numeFisier) {
        std::ifstream fin(numeFisier);
        if (!fin.is_open()) {
            std::cerr << "Eroare: nu s-a putut deschide fisierul " << numeFisier << "\n";
            return false;
        }

        matrice.clear();
        std::string linie;
        while (std::getline(fin, linie)) {
            matrice.push_back(linie);
        }

        fin.close();

        if (matrice.empty()) {
            std::cerr << "Eroare: fisierul este gol!\n";
            return false;
        }

        inaltime = matrice.size();
        latime = matrice[0].size();
        return true;
    }


    void afiseaza(int jucatorX, int jucatorY, const std::vector<std::pair<int, int>>& fantome, const std::vector<std::pair<int, int>>& energize) const {
           for (int y = 0; y < inaltime; ++y) {
               for (int x = 0; x < latime; ++x) {
                   bool desenat = false;
                    if (x== jucatorX && y == jucatorY) {
                        desenat = true;
                        std::cout<<'P';
                    }
                   if (!desenat) {
                       for (const auto& f: fantome) {
                           if (x== f.first && y == f.second) {
                             std::cout<< 'F';
                               desenat = true;
                               break;
                           }
                       }
                   }
                   if (!desenat) {
                       for (const auto& e : energize)
                           if (x== e.first && y == e.second) {
                               std::cout<< '$';
                               desenat = true;
                               break;
                           }
                   }
                   if (!desenat) {
                       std::cout<< matrice[y][x];
                   }

               }
               std::cout << '\n';
           }
       }

    void veziHarti() {
           std::cout<< "    Vizualizare harti disponibile momentan   \n";
           std::cout<<"1. Harta mica\n";
           std::cout<<"2. Harta medie\n";
           std::cout<<"3. Harta mare\n";
           std::cout<<"Alege una dintre optiuni pentru a o vizualiza: ";

           int opt;
           std::cin>>opt;
           if (std::cin.fail()) {
               std::cin.clear();
               std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
               std::cout << "Input invalid. Revenim la meniu.\n";
               return;
           }
           std::string numeFisier;
           switch (opt) {
               case 1: {numeFisier = "../maps/harta1.txt"; break;}
               case 2: {numeFisier = "../maps/harta2.txt"; break;}
               case 3: {numeFisier = "../maps/harta3.txt"; break;}
               case 0: return;
                   default: {
                       std::cout<< "Optiune invalida.\n";
                       return;
                   }
           }
           if (!incarca_din_fisier(numeFisier)) {
               std::cerr<< "eroare la incarcarea hartii.\n";
               return;
           }
           std::cout<< "---Harta selectata---\n";
           for (const auto& linie: matrice)
               std::cout<< linie << '\n';

           int puncte=0;
           for (const auto& linie : matrice)
               for (char c : linie)
                   if (c=='.') puncte++;
           std::cout <<"\nDimensiune: "<< inaltime<<"x "<<latime<<" | Puncte: "<< puncte << "\n";
            std::cout<< "Apasa ENTER pentru a reveni la maniu...";
           std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
           std::cin.get();
       }

    bool este_perete(int x, int y) const {
        if (!este_in_limite(x, y)) return true;
        return matrice[y][x] == '#';
    }


    bool este_punct(int x, int y) const {
        if (!este_in_limite(x, y)) return false;
        return matrice[y][x] == '.';
    }


    void sterge_punct(int x, int y) {
        if (este_in_limite(x, y) && matrice[y][x] == '.')
            matrice[y][x] = ' ';
    }

    bool are_puncte_ramase() const {
           for (const auto& linie : matrice)
               for (char c : linie)
                   if (c == '.') return true;
           return false;
       }



    [[maybe_unused]] getInaltime() const { return inaltime; }
    [[maybe_unused]] getLatime() const { return latime; }
    const std::vector<std::string>& getMatrice() const { return matrice; }

    friend std::ostream& operator<<(std::ostream& os, const Harta& h) {
        os << "Harta (" << h.latime << "x" << h.inaltime << "):\n";
        for (const auto& linie : h.matrice)
            os << linie << '\n';
        return os;
    }
};

#endif //OOP_HARTA_H