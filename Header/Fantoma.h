#ifndef FANTOMA_H
#define FANTOMA_H

#include "Entitate.h"
#include <string>

class Jucator;

class Fantoma : public Entitate {
public:
    enum class Personalitate { Random, Chaser, Runner, Stalker };

private:
    std::string culoare;
    Personalitate tip;
    Jucator* target; // pentru AI

public:
    Fantoma(int x, int y, Personalitate tip, Jucator* target, const std::string& culoare="");

    void update(const Harta& harta) override;
    void interact(Jucator& jucator) override;
    std::unique_ptr<Entitate> clone() const override;
    void print(std::ostream& os) const override;

    Personalitate getPersonalitate() const { return tip; }
};

#endif
