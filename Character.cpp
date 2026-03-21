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
        std::cout << "You already have 4 monsters. Choose one to replace: " << std::endl;
        return false;
    }
}

void Character::setName(std::string _name) {
    name = _name;
}

Character::~Character() {}