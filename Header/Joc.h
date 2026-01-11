#ifndef JOC_H
#define JOC_H

#include <vector>
#include <memory>
#include <chrono>
#include "Harta.h"
#include "Jucator.h"
#include "Entitate.h"
#include "Meniu.h"

class Joc {
    Harta harta;
    std::vector<std::unique_ptr<Entitate>> entitati;
    Jucator* jucator;
    Meniu meniu;
    bool ruleaza;
    char ultimaDirectie;

    // cat de des apar
    std::chrono::steady_clock::time_point nextEnergizerSpawn;
    int maxActiveEnergizers = 1; // cap
    int spawnMinMs = 5000;       // 5 sec
    int spawnMaxMs = 12000;      // 12 sec


    int selectedMapIndex = 1; // 1..3

    void scheduleNextEnergizer();
    void maybeSpawnEnergizer();
    bool isOccupiedByBlocking(int x, int y) const; // jucator/fantoma/perete
    int countActivePuncte() const;
    int countActiveEnergizers() const;

public:
    Joc();

    void porneste();
    bool pornesteJoc();
    void ruleazaJoc();
    void afiseaza();
    void veziHarti();
};

#endif
