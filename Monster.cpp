#include "Monster.h"

Monster::Monster() {}

Monster::Monster(std::string _name, int _hitPoints, int _damge, std::string asciiArtPath) {
    name = _name;
    hitPoints = _hitPoints;
    damage = _damge;

    std::ifstream asciiFile(asciiArtPath);
    std::string asciiLine;
    while (std::getline(asciiFile, asciiLine)) {
        appearance.push_back(asciiLine);
    }
}

std::string Monster::getName() {
    return name;
}

int Monster::getHitPoints() {
    return hitPoints;
}

int Monster::getDamage() {
    return damage;
}

std::vector<std::string> Monster::getAppearance() {
    return appearance;
}

void Monster::setName(std::string _name) {
    name = _name;
}

int Monster::takeDamage(int damage) {
    hitPoints -= damage;
    return hitPoints;
}

Monster::~Monster() {}