#include "Monster.h"
#include <fstream>
#include <iostream>

Monster::Monster() {}

Monster::Monster(std::string _name, int _hitPoints, int _damge, std::string asciiArtPath) {
    name = _name;
    hitPoints = _hitPoints;
    maxHitPoints = _hitPoints;
    damage = _damge;
    alive = true;

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

bool Monster::getStatus() const {
    return alive;
}

void Monster::setName(std::string& _name) {
    name = _name;
}

int Monster::takeDamage(int damage) {
    hitPoints -= damage;
    if (hitPoints <= 0) {
        alive = false;
    }
    return hitPoints;
}

int Monster::revive() {
    hitPoints = maxHitPoints;
    alive = true;
    return hitPoints;
}

Monster::~Monster() {}