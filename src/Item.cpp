#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Item.h"
#include "Monster.h"


Item::Item(std::string _name) {
    std::srand(std::time(0));
    name = _name;
    if (name == "Bomb") {
        itemEnum = ItemType::Bomb;
    } else if (name == "FireBomb") {
        itemEnum = ItemType::FireBomb;
    } else if (name == "ThunderBomb") {
        itemEnum = ItemType::ThunderBomb;
    } else if (name == "Club") {
        itemEnum = ItemType::Club;
    } else if (name == "IceCubes") {
        itemEnum = ItemType::IceCubes;
    } else if (name == "Curse") {
        itemEnum = ItemType::Curse;
    } else if (name == "Poison") {
        itemEnum = ItemType::Poison;
    } else {
        std::cout << "Item has an illegal name" << std::endl;
        exit(1);
    }
}

std::string Item::getName() {
    return name;
}

void Item::useItem(Monster& enemyMonster) {
    int percentage;
	percentage = rand() % 100 + 1;

    switch (itemEnum)
    {
    case ItemType::Bomb:
        std::cout << "using Bomb" << std::endl;
        enemyMonster.takeDamage(10);
        break;

    case ItemType::FireBomb:
        std::cout << "using FireBomb" << std::endl;
        if (percentage <= 35) {
            enemyMonster.setStatus("Stunned");
        }
        enemyMonster.takeDamage(5);
        break;

    case ItemType::ThunderBomb:
        std::cout << "using ThunderBomb" << std::endl;
        if (percentage <= 50) {
            enemyMonster.setStatus("Paralyzed");
        }
        enemyMonster.takeDamage(10);
        break;

    case ItemType::Club:
        std::cout << "using Club" << std::endl;
        enemyMonster.takeDamage(20);
        break;

    case ItemType::IceCubes:
        std::cout << "using IceCubes" << std::endl;
        if (percentage <= 80) {
            enemyMonster.setStatus("Frozen");
        }
        break;

    case ItemType::Curse:
        std::cout << "using Curse" << std::endl;
        if (enemyMonster.getStatus() != "") {
            if (percentage <= 80) {
                enemyMonster.setStatus("Curse");
            }
        } else {
            if (percentage <= 20) {
                enemyMonster.setStatus("Curse");
            }
        }

    case ItemType::Poison:
        std::cout << "using Poison" << std::endl;
        if (enemyMonster.getMaxHitPoints() != enemyMonster.getHitPoints()) {
            enemyMonster.setStatus("Poisoned");
        } else {
            if (percentage <= 20) {
                enemyMonster.setStatus("Poisoned");
            }
        }

        enemyMonster.takeDamage(10);
        break;

    default:
        std::cout << "NOTHING" << std::endl;
        break;
    }
}

Item::~Item() {}