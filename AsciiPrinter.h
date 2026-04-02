// ConsolePrinter Header file
#include <string>
#include <vector>
#include "Monster.h"
#pragma once

class AsciiPrinter {
    public:
        AsciiPrinter();
        void printFightScreen(const Monster&, const Monster&, const int);
        void printInventory(const std::vector<Monster>&) const;
        void printInventory(const std::vector<const Monster*>&) const;
        ~AsciiPrinter();
    private:
        Monster friendlyMonster;
        Monster enemyMonster;
};