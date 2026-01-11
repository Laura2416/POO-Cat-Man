#include "Energizer.h"
#include "Jucator.h"

Energizer::Energizer(int x,int y):Entitate(x,y),activ(true){}
bool Energizer::esteActiv() const { return activ; }
void Energizer::dezactiveaza(){ activ=false; }

void Energizer::update(const Harta&){}
void Energizer::interact(Jucator& j){
    if(activ && j.getX()==x && j.getY()==y){
        j.adaugaScor(50);
        j.activeazaInvincibilitate();
        activ=false;
    }
}
std::unique_ptr<Entitate> Energizer::clone() const { return std::make_unique<Energizer>(*this); }
void Energizer::print(std::ostream& os) const { os<<"Energizer ("<<x<<","<<y<<")"; }
