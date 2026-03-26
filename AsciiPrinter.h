// ConsolePrinter Header file
#include <string>
#include <vector>
#include "Monster.h"
#pragma once

class AsciiPrinter {
    public:
        AsciiPrinter();
        std::string getName();
        void setMonsters(std::vector<std::string>, std::vector<std::string>);

        void printFightScreen(std::string);
        void printInventory(std::vector<Monster>);
        void printInventory2(std::vector<Monster>);
        ~AsciiPrinter();
    private:
        std::vector<std::string> friendlyMonster;
        std::vector<std::string> enemyMonster;
        int screenWidth;
};