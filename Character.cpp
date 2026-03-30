#include "Character.h"

Character::Character() {}

Character::Character(std::string _name) {
    name = _name;
    inventorySize = 4;
}

std::string Character::getName() {
    return name;
}

std::vector<Monster>& Character::getInventory() {
    return inventory;
}

Monster Character::getChosenMonster() {
    return inventory[activeMonster];
}

bool Character::setChosenMonster(int idx) {
    if (0 < idx || idx <= inventory.size()) {
        activeMonster = idx-1;
        
        return true;
    }
    std::cout << "invalid input" << std::endl;
    return false;
}

bool Character::addMonster(Monster _monster) {
    if (inventory.size() < inventorySize) {
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