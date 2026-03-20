// ConsolePrinter Header file
#include <string>
#include <iostream>
#include <iomanip>
#include "AsciiPrinter.h"

AsciiPrinter::AsciiPrinter() {}

void AsciiPrinter::updateMonsters(std::vector<std::string> _friendlyMonster, std::vector<std::string> _enemyMonster) {
    friendlyMonster = _friendlyMonster;
    enemyMonster = _enemyMonster;
}

void AsciiPrinter::printScreen() {
    std::cout << "+============================================================+" << std::endl;
    std::cout << "|" << std::setw(61) << "|" << std::endl;
    for (int i = 0; i < friendlyMonster.size(); ++i){
        std::cout << std::left << std::setw(5) << "|"
              << std::setw(20) << friendlyMonster[i]
              << std::setw(5)<< "" << std::setw(2)<< "VS" << std::setw(5)<< ""
              << std::setw(20) << enemyMonster[i]
              << std::right << std::setw(5) << "|" << std::endl;
    }
    std::cout << "|" << std::setw(61) << "|" << std::endl;
    std::cout << "+============================================================+" << std::endl;
    std::cout << "|" << std::setw(61) << "|" << std::endl;
    std::cout << "|" << std::setw(61) << "|" << std::endl;
    std::cout << "+============================================================+" << std::endl;
}

AsciiPrinter::~AsciiPrinter() {}