#pragma once
#include "Entitate.h"
#include <chrono>

class Jucator : public Entitate {
    int vieti;
    int scor;
    bool invincibil;
    std::chrono::steady_clock::time_point startInv;

public:
    Jucator(int x, int y);

    int getVieti() const;
    int getScor() const;
    bool esteInvincibil() const;

    void pierdeViata();
    void adaugaScor(int);
    void activeazaInvincibilitate();

    void update(const Harta&) override;
    void interact(Jucator&) override;
    std::unique_ptr<Entitate> clone() const override;
    void print(std::ostream&) const override;

    void muta(char, const Harta&);
};
