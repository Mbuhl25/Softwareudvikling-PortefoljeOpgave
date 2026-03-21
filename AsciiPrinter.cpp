// ConsolePrinter Header file
#include <string>
#include <iostream>
#include <iomanip>
#include "AsciiPrinter.h"

AsciiPrinter::AsciiPrinter() {}

void AsciiPrinter::setMonsters(std::vector<std::string> _friendlyMonster, std::vector<std::string> _enemyMonster) {
    friendlyMonster = _friendlyMonster;
    enemyMonster = _enemyMonster;   
}

void AsciiPrinter::printFightScreen() {
    screenWidth = 51; // Greater than 50 and uneven
    std::cout << "+"; for (int i = 1; i < screenWidth; ++i) {std::cout << "=";}; std::cout << "+" << std::endl;
    
    std::cout << std::right << "|" << std::setw(screenWidth) << "|" << std::endl;
    for (int i = 0; i < friendlyMonster.size(); ++i){
        std::cout << std::left
              << std::setw(5) << "|"
              << std::setw(20) << friendlyMonster[i]
              << std::setw((screenWidth-20-20-5-5)/2)<< ""
              << std::setw(6)<< "VS"
              << std::setw((screenWidth-20-20-5-5)/2)<< ""
              << std::setw(20) << enemyMonster[i]
              << std::right << "|" << std::endl;
    }
    std::cout << "|" << std::setw(screenWidth) << "|" << std::endl;
    std::cout << "+"; for (int i = 1; i < screenWidth; ++i) {std::cout << "=";}; std::cout << "+" << std::endl;
    std::cout << "|" << std::setw(screenWidth) << "|" << std::endl;
    std::cout << "|" << std::setw(screenWidth) << "|" << std::endl;
    std::cout << "+"; for (int i = 1; i < screenWidth; ++i) {std::cout << "=";}; std::cout << "+" << std::endl;
}

void AsciiPrinter::printInventory(std::vector<Monster> _monsters) {
    screenWidth = 25*4;
    std::cout << "+"; for (int i = 1; i < screenWidth; ++i) {std::cout << "=";}; std::cout << "+" << std::endl;
    for (int i = 0; i < _monsters[0].getAppearance().size(); ++i){
        std::cout << std::left << std::setw(5) << "|"
              << std::setw(20) << _monsters[0].getAppearance()[i] << std::setw(5) << "|"
              << std::setw(20) << _monsters[1].getAppearance()[i] << std::setw(5) << "|"
              << std::setw(20) << _monsters[2].getAppearance()[i] << std::setw(5) << "|"
              << std::setw(20) << _monsters[3].getAppearance()[i] << std::setw(5) << "|"
              << std::endl;
    }
    std::cout << "+"; for (int i = 1; i < screenWidth; ++i) {std::cout << "=";}; std::cout << "+" << std::endl;
}

AsciiPrinter::~AsciiPrinter() {}