#include "Entitate.h"

Entitate::Entitate(int x, int y) : x(x), y(y) {}

int Entitate::getX() const { return x; }
int Entitate::getY() const { return y; }

std::ostream& operator<<(std::ostream& os, const Entitate& e) {
    e.print(os);
    return os;
}