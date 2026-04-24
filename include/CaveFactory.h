#ifndef CAVE_H
#define CAVE_H

#include "Character.h"
#include "Monster.h"

class CaveFactory
{
public:
    CaveFactory();
    const std::vector<Monster>& getMonsterList(int tier) const;
    const int EstimatePlayerLevel(const Character&) const;
    Monster findMatchingPowerLevel(int);
    Character createEnemy(int);
    ~CaveFactory();
private:
    std::vector<Monster> allMonsters;
    std::vector<Monster> tier1Monsters;
    std::vector<Monster> tier2Monsters;
};

#endif