// ConsolePrinter Header file
#include <string>
#include <iostream>
#include <iomanip>
#include "AsciiPrinter.h"

AsciiPrinter::AsciiPrinter() {}

void AsciiPrinter::printFightScreen(const Monster& friendlyMonster, const Monster& enemyMonster, const int monsterturn) {
    int screenWidth = 71; // Greater than 50 and uneven

    std::string displayName;
    if (monsterturn == 0 || monsterturn == 2) {
        displayName = friendlyMonster.getName();
    } else if (monsterturn == 1) {
        displayName = enemyMonster.getName();
    }

    std::cout << "+"; for (int i = 1; i < screenWidth; ++i) {std::cout << "=";}; std::cout << "+" << std::endl;
    
    std::cout << "|" << std::left << std::setw(screenWidth-1) << "  It is now " + displayName + "'s turn to make a move" << "|" << std::right << std::endl;
    std::cout << "|" << std::setw(screenWidth) << "|" << std::endl;
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
        << std::setw(4) << "HP: " << std::setw(16) << std::to_string(friendlyMonster.getHitPoints()) + "/" + std::to_string(friendlyMonster.getMaxHitPoints())
        << std::setw((screenWidth-20-20-5-5)/2)<< ""
        << std::setw(6)<< ""
        << std::setw((screenWidth-20-20-5-5)/2)<< ""
        << std::setw(4) << "HP: " << std::setw(16) << std::to_string(enemyMonster.getHitPoints()) + "/" + std::to_string(enemyMonster.getMaxHitPoints())
        << std::right << "|" << std::endl;
    std::cout << std::left << std::setw(5) << "|"
        << std::setw(10) << "Strength: " << std::setw(10) << friendlyMonster.getDamage()
        << std::setw((screenWidth-20-20-5-5)/2)<< ""
        << std::setw(6)<< " "
        << std::setw((screenWidth-20-20-5-5)/2)<< ""
        << std::setw(10) << "Strength: " << std::setw(10) << enemyMonster.getDamage()
        << std::right << "|" << std::endl;
    std::cout << std::left << std::setw(5) << "|"
        << std::setw(10) << "status: " << std::setw(10) << friendlyMonster.getStatus()
        << std::setw((screenWidth-20-20-5-5)/2)<< ""
        << std::setw(6)<< " "
        << std::setw((screenWidth-20-20-5-5)/2)<< ""
        << std::setw(10) << "status: " << std::setw(10) << enemyMonster.getStatus()
        << std::right << "|" << std::endl;
    
    
    std::cout << "+"; for (int i = 1; i < screenWidth; ++i) {std::cout << "=";}; std::cout << "+" << std::endl;
    if (monsterturn == 0) {
        std::cout << "|" << std::left << std::setw(screenWidth-1) << "  What would you like to do?" << "|" << std::right << std::endl;
        std::cout << "|" << std::left << std::setw(screenWidth-1) << "    [1] Attack" << "|" << std::right << std::endl;
        std::cout << "|" << std::left << std::setw(screenWidth-1) << "    [2] Switch Monster" << "|" << std::right << std::endl;
        std::cout << "|" << std::left << std::setw(screenWidth-1) << "    [3] Use an Item from the Monster" << "|" << std::right << std::endl;
    } else if (monsterturn == 1) {
        std::cout << "|" << std::left << std::setw(screenWidth-1) << "  " + displayName + " Chooses to attack" << "|" << std::right << std::endl;
    } else if (monsterturn == 2) {
        std::cout << "|" << std::left << std::setw(screenWidth-1) << "  Do you wish to catch " + enemyMonster.getName() + "?" << "|" << std::right << std::endl;
        std::cout << "|" << std::left << std::setw(screenWidth-1) << "    [1] Catch" << "|" << std::right << std::endl;
        std::cout << "|" << std::left << std::setw(screenWidth-1) << "    [2] Let it die slowly and painfully" << "|" << std::right << std::endl;
    }

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
    // print asciiArt
    for (int line = 0; line < _monsters[0].getAppearance().size(); ++line){
        std::cout << std::left << std::setw(5) << "|";
        for (int i = 0; i < _monsters.size(); ++i){
            std::cout << std::setw(20) << _monsters[i].getAppearance()[line]
            << std::setw(5) << "|";
        }
        std::cout << std::endl;
    }
    std::cout << "+"; for (int i = 1; i < screenWidth*_monsters.size(); ++i) {std::cout << "=";}; std::cout << "+" << std::endl;
    // print damage
    for (int i = 0; i < _monsters.size(); ++i){
        std::cout << std::left << std::setw(3) << "|" << std::setw(screenWidth-3) << "Damage: " + std::to_string(_monsters[i].getDamage());
    }
    std::cout << "|" << std::endl;
    // print HP
    for (int i = 0; i < _monsters.size(); ++i){
        std::cout << std::left << std::setw(3) << "|" << std::setw(screenWidth-3) << "HP: " + std::to_string(_monsters[i].getHitPoints()) + " of " + std::to_string(_monsters[i].getMaxHitPoints());
    }
    std::cout << "|" << std::endl;
    // print status
    for (int i = 0; i < _monsters.size(); ++i){
        std::cout << std::left << std::setw(3) << "|" << std::setw(screenWidth-3) << "Status: " + _monsters[i].getStatus();
    }
    std::cout << "|" << std::endl;

    // print Items
    for (int i = 0; i < _monsters.size(); ++i){
        std::string itemStrings;
        for (int j = 0; j < _monsters[i].getItemList().size(); ++j) {
            itemStrings += _monsters[i].getItemList()[j].getName() + ", ";
        }
        std::cout << std::left << std::setw(3) << "|" << std::setw(screenWidth-3) << "Item: " + itemStrings;
    }

    std::cout << "|" << std::endl;
    std::cout << "+"; for (int i = 1; i < screenWidth*_monsters.size(); ++i) {std::cout << "=";}; std::cout << "+" << std::endl;
}

AsciiPrinter::~AsciiPrinter() {}