#include "Monster.h"

Monster::Monster() {}

Monster::Monster(std::string _name, int _hitPoints, int _damge) {
    name = _name;
    hitPoints = _hitPoints;
    damage = _damge;
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

void Monster::setName(std::string _name) {
    name = _name;
}

int Monster::takeDamage(int damage) {
    hitPoints -= damage;
    return hitPoints;
}

Monster::~Monster() {}