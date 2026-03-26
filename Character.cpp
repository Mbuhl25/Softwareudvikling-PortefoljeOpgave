#include "Character.h"

Character::Character() {}

Character::Character(std::string _name) {
    name = _name;
}

std::string Character::getName() {
    return name;
}

std::vector<Monster>& Character::getInventory() {
    return inventory;
}

bool Character::addMonster(Monster _monster) {
    if (inventory.size() < 4) {
        inventory.push_back(_monster);
        return true;
    }
    else {
        inventory.push_back(_monster);
        return false;
    }
}

void Character::removeMonster(int index) {
    inventory.erase(inventory.begin() + index-1);
}

void Character::setName(std::string _name) {
    name = _name;
}

Character::~Character() {}