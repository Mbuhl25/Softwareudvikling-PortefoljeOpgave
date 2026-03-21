// ConsolePrinter Header file
#include <string>
#include <iostream>
#include <iomanip>
#include "AsciiPrinter.h"

AsciiPrinter::AsciiPrinter() {
    screenWidth = 51;
    if (screenWidth < 51 || screenWidth % 2 == 0) {
        std::cout << "ScreenWidth is either too small ( < 51 ), or even, which is illegal";
        exit(1);
    }
}

void AsciiPrinter::updateMonsters(std::vector<std::string> _friendlyMonster, std::vector<std::string> _enemyMonster) {
    friendlyMonster = _friendlyMonster;
    enemyMonster = _enemyMonster;
    
}

void AsciiPrinter::printScreen() {
    std::cout << (screenWidth-20-20-5-5)/2 << std::endl;
    std::cout << "+"; for (int i = 1; i < screenWidth; ++i) {std::cout << "=";}; std::cout << "+" << std::endl;
    
    std::cout << "|" << std::setw(screenWidth) << "|" << std::endl;
    for (int i = 0; i < friendlyMonster.size(); ++i){
        std::cout << std::left
              << std::setw(5) << "|"
              << std::setw(20) << friendlyMonster[i]
              << std::setw((screenWidth-20-20-5-5)/2)<< ""
              << std::setw(2)<< "VS"
              << std::setw((screenWidth-20-20-5-5)/2)<< ""
              << std::setw(20) << enemyMonster[i]
              << std::right << std::setw(5) << "|" << std::endl;
    }
    std::cout << "|" << std::setw(screenWidth) << "|" << std::endl;
    std::cout << "+"; for (int i = 1; i < screenWidth; ++i) {std::cout << "=";}; std::cout << "+" << std::endl;
    std::cout << "|" << std::setw(screenWidth) << "|" << std::endl;
    std::cout << "|" << std::setw(screenWidth) << "|" << std::endl;
    std::cout << "+"; for (int i = 1; i < screenWidth; ++i) {std::cout << "=";}; std::cout << "+" << std::endl;
}

AsciiPrinter::~AsciiPrinter() {}