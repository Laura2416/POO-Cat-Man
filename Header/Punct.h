#pragma once
#include "Entitate.h"

class Punct : public Entitate {
    bool activ;
public:
    Punct(int,int);

    void update(const Harta&) override {}
    void interact(Jucator&) override;
    std::unique_ptr<Entitate> clone() const override;
    void print(std::ostream&) const override;

    bool esteActiv() const;
};
