// ConsolePrinter Header file
#include <string>
#pragma once

class AsciiPrinter {
    public:
        AsciiPrinter();
        AsciiPrinter(std::string, std::string);
        std::string getName();
        void updateMonsters(std::string, std::string);
        void updateBorder(std::string);
        void updateEnviroment(std::string);
        void printScreen();
        ~AsciiPrinter();
    private:
        std::string friendlyMonster;
        std::string enemyMonster;
        std::string border;
        std::string environment;
};