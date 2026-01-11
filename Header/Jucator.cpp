#include "Jucator.h"
#include "Harta.h"

Jucator::Jucator(int x, int y)
    : Entitate(x,y), vieti(3), scor(0), invincibil(false) {}

int Jucator::getVieti() const { return vieti; }
int Jucator::getScor() const { return scor; }

bool Jucator::esteInvincibil() const {
    if (!invincibil) return false;
    auto t = std::chrono::steady_clock::now() - startInv;
    return std::chrono::duration_cast<std::chrono::seconds>(t).count() < 3;
}


void Jucator::pierdeViata() { if (vieti > 0) vieti--; }
void Jucator::adaugaScor(int s) { scor += s; }

void Jucator::activeazaInvincibilitate() {
    invincibil = true;
    startInv = std::chrono::steady_clock::now();
}

void Jucator::muta(char c, const Harta& h) {
    int nx=x, ny=y;
    if (c=='w') ny--;
    if (c=='s') ny++;
    if (c=='a') nx--;
    if (c=='d') nx++;
    if (!h.estePerete(nx,ny)) { x=nx; y=ny; }
}

void Jucator::update(const Harta&) {}
void Jucator::interact(Jucator&) {}
std::unique_ptr<Entitate> Jucator::clone() const { return std::make_unique<Jucator>(*this); }

void Jucator::print(std::ostream& os) const {
    os<<"Jucator ("<<x<<","<<y<<") vieti="<<vieti<<" scor="<<scor;
}
