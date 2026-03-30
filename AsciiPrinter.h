// ConsolePrinter Header file
#include <string>
#include <vector>
#include "Monster.h"
#pragma once

class AsciiPrinter {
    public:
        AsciiPrinter();
        void setMonsters(const std::vector<std::string>&, const std::vector<std::string>&);
        void printFightScreen(const std::string&) const;
        void printInventory(const std::vector<Monster>&) const;
        void printInventory(const std::vector<const Monster*>&) const;
        ~AsciiPrinter();
    private:
        std::vector<std::string> friendlyMonster;
        std::vector<std::string> enemyMonster;
};