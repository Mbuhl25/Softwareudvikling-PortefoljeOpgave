// ConsolePrinter Header file
#include <string>
#include <vector>
#pragma once

class AsciiPrinter {
    public:
        AsciiPrinter();
        std::string getName();
        void updateMonsters(std::vector<std::string>, std::vector<std::string>);
        void printFightScreen();
        void printScreen();
        ~AsciiPrinter();
    private:
        std::vector<std::string> friendlyMonster;
        std::vector<std::string> enemyMonster;
        int screenWidth;
};