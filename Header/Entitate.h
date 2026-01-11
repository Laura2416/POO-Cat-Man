#pragma once
#include <memory>
#include <iosfwd>

class Harta;
class Jucator;


class Entitate {
protected:
    int x, y;

public:
    Entitate(int x, int y);
    virtual ~Entitate() = default;

    int getX() const;
    int getY() const;

    virtual void update(const Harta&) = 0;
    virtual void interact(Jucator&) = 0;
    virtual std::unique_ptr<Entitate> clone() const = 0;
    virtual void print(std::ostream&) const = 0;
};
std::ostream& operator<<(std::ostream& os, const Entitate& e);
