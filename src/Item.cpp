#include <iostream>
#include "Item.h"


Item::Item(std::string _name, std::string _status) {
    name = _name;
    if (name == "Bomb") {
        itemEnum = ItemType::Bomb;
    } else if (name == "FireBomb") {
        itemEnum = ItemType::FireBomb;
    } else if (name == "Poison") {
        itemEnum = ItemType::Poison;
    }
}

void Item::setName(std::string _name) {
    name = _name;
}

std::string Item::getName() {
    return name;
}

std::string Item::getStatus() {
    return status;
}

void Item::useItem(Monster& enemyMonster) {
    switch (itemEnum)
    {
    case ItemType::Bomb:
        std::cout << "BOMB" << std::endl;
        enemyMonster.takeDamage(10);
        break;
    case ItemType::FireBomb:
        std::cout << "FIREBOMB" << std::endl;
        enemyMonster.takeDamage(5);
        break;
    case ItemType::Poison:
        std::cout << "Club" << std::endl;
        enemyMonster.takeDamage(20);
        break;
    default:
        std::cout << "NOTHING" << std::endl;
        break;
    }
}

Item::~Item() {}