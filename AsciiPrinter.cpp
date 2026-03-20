// ConsolePrinter Header file
#include <string>
#include <iostream>
#include <iomanip>
#include "AsciiPrinter.h"

AsciiPrinter::AsciiPrinter() {}

AsciiPrinter::AsciiPrinter(std::string _border, std::string _enviroment) {
    border = _border;
    environment = _enviroment;
}

void AsciiPrinter::updateMonsters(std::string _friendlyMonster, std::string _enemyMonster) {
    friendlyMonster = _friendlyMonster;
    enemyMonster = _enemyMonster;
}

void AsciiPrinter::updateBorder(std::string _border) {
    border = _border;
}

void AsciiPrinter::updateEnviroment(std::string _environment) {
    environment = _environment;
}

void AsciiPrinter::printScreen() {
    std::cout << "+=============================================================+" << std::endl;
    std::cout << "|" << std::setw(62) << "|" << std::endl;
    std::cout << "|" << std::setw(25) << " " << std::setw(12) << " " << std::setw(25) << "|" << std::endl;
    std::cout << "|" << std::setw(25) << " " << std::setw(12) << " " << std::setw(25) << "|" << std::endl;
    std::cout << "|" << std::setw(25) << " " << std::setw(12) << " " << std::setw(25) << "|" << std::endl;
    std::cout << "|" << std::setw(25) << " " << std::setw(12) << " " << std::setw(25) << "|" << std::endl;
    std::cout << "|" << std::setw(25) << " " << std::setw(12) << " " << std::setw(25) << "|" << std::endl;
    std::cout << "|" << std::setw(25) << " " << std::setw(12) << " " << std::setw(25) << "|" << std::endl;
    std::cout << "|" << std::setw(62) << "|" << std::endl;
    std::cout << "+=============================================================+" << std::endl;
    std::cout << "|" << std::setw(62) << "|" << std::endl;
    std::cout << "|" << std::setw(62) << "|" << std::endl;
    std::cout << "+=============================================================+" << std::endl;
}

AsciiPrinter::~AsciiPrinter() {}