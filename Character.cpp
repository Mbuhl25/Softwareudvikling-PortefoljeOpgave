#include "Character.h"
#include <iostream>

Character::Character() {}

Character::Character(std::string _name) {
    name = _name;
    inventorySize = 4;
    activeMonster = -1;
}

const std::string& Character::getName() const {
    return name;
}

const std::vector<Monster>& Character::getInventory() const{
    return inventory;
}

const Monster& Character::getChosenMonster() const {
    if (activeMonster < 0 || activeMonster >= inventory.size()) {
        throw std::logic_error("No active monster selected");
    }
    return inventory[activeMonster];
}


bool Character::setChosenMonster(int idx) {
    if (0 < idx && idx <= inventory.size()) {
        activeMonster = idx-1;
        std::cout << "ooooo: " << activeMonster << std::endl;
        return true;
    }
    std::cout << "invalid input" << std::endl;
    return false;
}

bool Character::addMonster(const Monster& _monster) {
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

void Character::setName(const std::string& _name) {
    name = _name;
}

Character::~Character() {}