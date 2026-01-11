#include "Punct.h"
#include "Jucator.h"

Punct::Punct(int x,int y) : Entitate(x,y), activ(true) {}

bool Punct::esteActiv() const { return activ; }

void Punct::interact(Jucator& j) {
    if (activ && j.getX()==x && j.getY()==y) {
        j.adaugaScor(10);
        activ=false;
    }
}

std::unique_ptr<Entitate> Punct::clone() const {
    return std::make_unique<Punct>(*this);
}

void Punct::print(std::ostream& os) const {
    os<<"Punct ("<<x<<","<<y<<")";
}
