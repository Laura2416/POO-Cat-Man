#include "Fantoma.h"
#include "Harta.h"
#include "Jucator.h"
#include <cstdlib>
#include <vector>
#include <cmath>

Fantoma::Fantoma(int x, int y, Personalitate t, Jucator* tgt, const std::string& c)
    : Entitate(x, y), culoare(c), tip(t), target(tgt) {}

void Fantoma::update(const Harta& h) {
    // miscari
    struct Move { int dx, dy; };
    static const Move moves[4] = { {0,-1},{0,1},{-1,0},{1,0} };

    auto manhattan = [&](int ax,int ay,int bx,int by){ return std::abs(ax-bx)+std::abs(ay-by); };

    std::vector<std::pair<int,int>> opts;
    opts.reserve(4);
    for (auto m : moves) {
        int nx = x + m.dx, ny = y + m.dy;
        if (!h.estePerete(nx, ny)) opts.emplace_back(nx, ny);
    }
    if (opts.empty()) return;

    int bestIdx = 0;
    if (!target) {
        bestIdx = rand() % (int)opts.size();
    } else {
        // personalitate
        if (tip == Personalitate::Random) {
            bestIdx = rand() % (int)opts.size();
        } else if (tip == Personalitate::Chaser) {
            int best = 1e9;
            for (int i=0;i<(int)opts.size();++i){
                int d = manhattan(opts[i].first, opts[i].second, target->getX(), target->getY());
                if (d < best) { best=d; bestIdx=i; }
            }
        } else if (tip == Personalitate::Runner) {
            int best = -1;
            for (int i=0;i<(int)opts.size();++i){
                int d = manhattan(opts[i].first, opts[i].second, target->getX(), target->getY());
                if (d > best) { best=d; bestIdx=i; }
            }
        } else if (tip == Personalitate::Stalker) {
            // vine la tine dar sta la 2 pozitii distanta
            int bestScore = 1e9;
            for (int i=0;i<(int)opts.size();++i){
                int d = manhattan(opts[i].first, opts[i].second, target->getX(), target->getY());
                int score = std::abs(d - 2);
                if (score < bestScore) { bestScore=score; bestIdx=i; }
            }
        }
    }

    x = opts[bestIdx].first;
    y = opts[bestIdx].second;
}

void Fantoma::interact(Jucator& j) {
    if (j.getX() == x && j.getY() == y && !j.esteInvincibil()) {
        j.pierdeViata();
    }
}

std::unique_ptr<Entitate> Fantoma::clone() const {
    return std::make_unique<Fantoma>(*this);
}

void Fantoma::print(std::ostream& os) const {
    os << "Fantoma (" << x << "," << y << ")";
}
