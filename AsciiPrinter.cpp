// ConsolePrinter Header file
#include <string>
#include <iostream>
#include <iomanip>
#include "AsciiPrinter.h"

AsciiPrinter::AsciiPrinter() {}

void AsciiPrinter::setMonsters(const Monster& _friendlyMonster, const Monster& _enemyMonster) {
    friendlyMonster = _friendlyMonster;
    enemyMonster = _enemyMonster;   
}

void AsciiPrinter::printFightScreen(const std::string& monstersTurn) const {
    int screenWidth = 71; // Greater than 50 and uneven
    std::cout << "+"; for (int i = 1; i < screenWidth; ++i) {std::cout << "=";}; std::cout << "+" << std::endl;
    
    std::cout << std::right << "|" << std::setw(screenWidth) << "|" << std::endl;
    for (int i = 0; i < friendlyMonster.getAppearance().size(); ++i){
        std::cout << std::left
            << std::setw(5) << "|"
            << std::setw(20) << friendlyMonster.getAppearance()[i]
            << std::setw((screenWidth-20-20-5-5)/2)<< ""
            << std::setw(6)<< "VS"
            << std::setw((screenWidth-20-20-5-5)/2)<< ""
            << std::setw(20) << enemyMonster.getAppearance()[i]
            << std::right << "|" << std::endl;
    }
    std::cout << "|" << std::setw(screenWidth) << "|" << std::endl;
    std::cout << std::left << std::setw(5) << "|"
        << std::setw(4) << "HP: " << std::setw(16) << friendlyMonster.getHitPoints()
        << std::setw((screenWidth-20-20-5-5)/2)<< ""
        << std::setw(6)<< "VS"
        << std::setw((screenWidth-20-20-5-5)/2)<< ""
        << std::setw(4) << "HP: " << std::setw(16) << enemyMonster.getHitPoints()
        << std::right << "|" << std::endl;
    std::cout << "+"; for (int i = 1; i < screenWidth; ++i) {std::cout << "=";}; std::cout << "+" << std::endl;
    std::cout << "|" << std::left << std::setw(screenWidth-1) << "  It is now " + monstersTurn + "'s turn to make a move" << "|" << std::right << std::endl;
    std::cout << "|" << std::setw(screenWidth) << "|" << std::endl;
    std::cout << "+"; for (int i = 1; i < screenWidth; ++i) {std::cout << "=";}; std::cout << "+" << std::endl;
}

void AsciiPrinter::printInventory(const std::vector<Monster>& _monsters) const {
    int screenWidth = 25;
    std::cout << "+"; for (int i = 1; i < screenWidth*_monsters.size(); ++i) {std::cout << "=";}; std::cout << "+" << std::endl;
    // print numbers above
    for (int i = 0; i < _monsters.size(); ++i){
        std::cout << std::left << std::setw(3) << "|" << std::setw(screenWidth-3) << i+1;
    }
    std::cout << "|" << std::endl;
    
    for (int line = 0; line < _monsters[0].getAppearance().size(); ++line){
        std::cout << std::left << std::setw(5) << "|";
        for (int i = 0; i < _monsters.size(); ++i){
            std::cout << std::setw(20) << _monsters[i].getAppearance()[line]
            << std::setw(5) << "|";
        }
        std::cout << std::endl;
    }
    std::cout << "+"; for (int i = 1; i < screenWidth*_monsters.size(); ++i) {std::cout << "=";}; std::cout << "+" << std::endl;
}

AsciiPrinter::~AsciiPrinter() {}