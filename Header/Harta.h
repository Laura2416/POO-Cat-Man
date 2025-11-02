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

    // === Constructor cu parametru ===
    explicit Harta(const std::string& fisier) {
        incarca_din_fisier(fisier);
    }

    // === Constructor de copiere ===
    Harta(const Harta& other)
        : matrice(other.matrice), inaltime(other.inaltime), latime(other.latime) {
        std::cout << "[DEBUG] Constructor de copiere apelat pentru Harta\n";
    }

    // === Operator de copiere ===
    Harta& operator=(const Harta& other) {
        if (this != &other) {
            matrice = other.matrice;
            inaltime = other.inaltime;
            latime = other.latime;
        }
        std::cout << "[DEBUG] Operator= apelat pentru Harta\n";
        return *this;
    }

    // === Destructor ===
    ~Harta() {
        std::cout << "[DEBUG] Destructor apelat pentru Harta\n";
        matrice.clear();
    }

    // === Functie de incarcare a hartii din fisier ===
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

    // === Afișare hartă ===
    void afiseaza() const {
        for (const auto& linie : matrice)
            std::cout << linie << '\n';
    }

    // === Verifică dacă o poziție e perete ===
    bool este_perete(int x, int y) const {
        if (!este_in_limite(x, y)) return true;
        return matrice[y][x] == '#';
    }

    // === Verifică dacă e un punct de mâncare ===
    bool este_punct(int x, int y) const {
        if (!este_in_limite(x, y)) return false;
        return matrice[y][x] == '.';
    }

    // === Șterge punctul (după ce e mâncat) ===
    void sterge_punct(int x, int y) {
        if (este_in_limite(x, y) && matrice[y][x] == '.')
            matrice[y][x] = ' ';
    }

    // === Getteri ===
    int getInaltime() const { return inaltime; }
    int getLatime() const { return latime; }

    // === Operator << pentru afișare ===
    friend std::ostream& operator<<(std::ostream& os, const Harta& h) {
        os << "Harta (" << h.latime << "x" << h.inaltime << "):\n";
        for (const auto& linie : h.matrice)
            os << linie << '\n';
        return os;
    }
};

#endif //OOP_HARTA_H