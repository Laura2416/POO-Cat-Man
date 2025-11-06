#ifndef JOC_H
#define JOC_H

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <ctime>

#include "Jucator.h"
#include "Fantoma.h"
#include "Harta.h"

// ==========================
// 🔹 Compatibilitate tastatură
// ==========================
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

int _kbhit() {
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF) {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

int _getch() {
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

// ==========================
// 🔹 Clasa Joc
// ==========================
class Joc {
private:
    Harta harta;
    Jucator jucator;
    std::vector<Fantoma> fantome;
    bool ruleaza;

    // --- Funcție privată: verifică coliziuni ---
    void verifica_coliziuni() {
        for (auto& f : fantome) {
            if (f.getX() == jucator.getX() && f.getY() == jucator.getY()) {
                std::cout << " Ai fost prins de o fantomă!\n";
                jucator.pierdeViata();
                if (jucator.getVieti() == 0) {
                    ruleaza = false;
                    std::cout << "\nGAME OVER!\n";
                }
            }
        }
    }

public:
    // --- Constructor ---
    Joc() : ruleaza(true) {
        srand(static_cast<unsigned>(time(nullptr)));
    }

    // --- Inițializare joc ---
    bool porneste() {
        if (!harta.incarca_din_fisier("../Header/harta.txt")) {
            std::cerr << "Eroare la încărcarea hărții.\n";
            return false;
        }

        jucator = Jucator(2, 2);
        fantome.push_back(Fantoma(10, 3, "albastră"));
        fantome.push_back(Fantoma(15, 4, "roșie"));
        return true;
    }

    // --- Afișare starea curentă ---
    void afiseaza() {
        // Mută cursorul la începutul terminalului (fără a șterge tot)
        std::cout << "\033[H\033[J";  // "escape sequence" pentru cursor + clear parțial

        std::vector<std::pair<int, int>> pozFantome;
        for (const auto& f : fantome)
            pozFantome.emplace_back(f.getX(), f.getY());

        harta.afiseaza(jucator.getX(), jucator.getY(), pozFantome);
        std::cout << "\n Scor: " << jucator.getScor() << "    Vieți: " << jucator.getVieti() << "\n";
        std::cout << "(W/A/S/D pentru mișcare, Q pentru ieșire)\n";
    }

    // --- Actualizare logică joc ---
    void actualizeaza() {
        if (_kbhit()) {
            char tasta = _getch();
            int nouX = jucator.getX();
            int nouY = jucator.getY();

            switch (tasta) {
                case 'w': nouY--; break;
                case 's': nouY++; break;
                case 'a': nouX--; break;
                case 'd': nouX++; break;
                case 'q': ruleaza = false; return;
                default: return;
            }

            if (!harta.este_perete(nouX, nouY)) {
                jucator.setPozitie(nouX, nouY);
                if (harta.este_punct(nouX, nouY)) {
                    jucator.manancaPunct();
                    harta.sterge_punct(nouX, nouY);
                }
            }
        }

        // mișcare fantome
        for (auto& f : fantome)
            f.muta_random(harta);

        verifica_coliziuni();
    }

    // --- Rulează jocul ---
    void ruleaza_joc() {
        if (!porneste()) return;

        while (ruleaza) {
            afiseaza();
            actualizeaza();
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
        }
    }

    // --- Operator << pentru afișare ---
    friend std::ostream& operator<<(std::ostream& os, const Joc& j) {
        os << "Joc cu " << j.fantome.size() << " fantome și un jucător.\n";
        os << j.harta;
        return os;
    }
};

#endif
