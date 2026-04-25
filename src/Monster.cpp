#include <fstream>
#include <iostream>
#include "Monster.h"

Monster::Monster() {}

Monster::Monster(std::string _name, int _hitPoints, int _damge, std::string asciiArtPath) {
    name = _name;
    hitPoints = _hitPoints;
    maxHitPoints = _hitPoints;
    damage = _damge;
    status = "";

    std::ifstream asciiFile(asciiArtPath);
    if (asciiFile.fail()) {
        std::cout << "Couldn't open file: " << asciiArtPath << std::endl;
        exit(1);
    }
    std::string asciiLine;
    while (std::getline(asciiFile, asciiLine)) {
        appearance.push_back(asciiLine);
    }
}

const std::string& Monster::getName() const {
    return name;
}

int Monster::getHitPoints() const {
    return hitPoints;
}

int Monster::getMaxHitPoints() const {
    return maxHitPoints;
}

int Monster::getDamage() const {
    return damage;
}

const std::vector<std::string>& Monster::getAppearance() const {
    return appearance;
}

std::string Monster::getStatus() const {
    return status;
}

std::vector<Item> Monster::getItemList() const {
    return itemList;
}

void Monster::setName(std::string& _name) {
    name = _name;
}

void Monster::setStatus(std::string _status) {
    status = _status;
}

int Monster::takeDamage(int damage) {
    hitPoints -= damage;
    if (hitPoints <= 0) {
        status = "Fainted";
    }
    return hitPoints;
}

int Monster::revive() {
    hitPoints = maxHitPoints;
    status = "";
    return hitPoints;
}

void Monster::addItem(Item item) {
    itemList.push_back(item);
}

Monster::~Monster() {}