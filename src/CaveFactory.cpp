#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "CaveFactory.h"

CaveFactory::CaveFactory() {
    std::srand(std::time(0));

    // Initialize a vector with objects for every monster
    allMonsters = {
    Monster("Wiggly Worm",        5,    5, "../AsciiArt/Worm.txt"),
    Monster("Dizzy Duckling",     10,   5, "../AsciiArt/Duckling.txt"),
    Monster("Creepy Cockroach",   10,  10, "../AsciiArt/Cockroach.txt"),
    Monster("Mighty Mouse",       10,  15, "../AsciiArt/Mouse.txt"),
    Monster("Buzzing Bee",        10,  20, "../AsciiArt/Bee.txt"),
    Monster("Flipping Fish",      25,  10, "../AsciiArt/Fish.txt"),
    Monster("Fierce Frog",        25,  15, "../AsciiArt/Frog.txt"),
    Monster("Bad Bat",            20,  25, "../AsciiArt/Bat.txt"),
    Monster("Raging Rabbit",      35,  15, "../AsciiArt/Rabbit.txt"),
    Monster("Savage Spider",      5,   50, "../AsciiArt/Spider.txt"),
    Monster("Sneaky Squirrel",    30,  30, "../AsciiArt/Squirrel.txt"),
    Monster("Punchy Penguin",     40,  25, "../AsciiArt/Penguin.txt"),
    Monster("Observant Owl",      40,  30, "../AsciiArt/Owl.txt"),
    Monster("Clever Cat",         45,  40, "../AsciiArt/Cat.txt"),
    Monster("Prickly Porcupine",  65,  30, "../AsciiArt/Porcupine.txt"),
    Monster("Dashing Deer",       75,  30, "../AsciiArt/Deer.txt"),
    Monster("Confused Cow",       100, 20, "../AsciiArt/Cow.txt"),
    Monster("Hardy Horse",        90,  40, "../AsciiArt/Horse.txt"),
    Monster("Enormous Elephant",  100, 50, "../AsciiArt/Elephant.txt"),
    Monster("Devious Dragon",     100, 100, "../AsciiArt/Dragon.txt"),
    };

    tier1Monsters = {
    Monster("Wiggly Worm",        5,    5, "../AsciiArt/Worm.txt"),
    Monster("Dizzy Duckling",     10,   5, "../AsciiArt/Duckling.txt"),
    Monster("Creepy Cockroach",   10,  10, "../AsciiArt/Cockroach.txt"),
    Monster("Mighty Mouse",       10,  15, "../AsciiArt/Mouse.txt"),
    Monster("Buzzing Bee",        10,  20, "../AsciiArt/Bee.txt"),
    Monster("Flipping Fish",      25,  10, "../AsciiArt/Fish.txt"),
    Monster("Fierce Frog",        25,  15, "../AsciiArt/Frog.txt"),
    };

    tier2Monsters = {
    Monster("Devious Dragon",     100, 100, "../AsciiArt/Dragon.txt"),
    };

    allItems = {
        Item("Bomb"),
        Item("FireBomb"),
        Item("ThunderBomb"),
        Item("Club"),
        Item("IceCubes"),
        Item("Curse"),
        Item("Poison"),
    };
}

const std::vector<Monster>& CaveFactory::getMonsterList(int tier) const {
    if (tier == 0) {
        return allMonsters;
    } else if (tier == 1) {
        return tier1Monsters;
    } else if (tier == 2) {
        return tier2Monsters;
    } else {
        std::cout << "Not a valid tier of monsters" << std::endl;
        exit(0);
    }
}

const int CaveFactory::EstimatePlayerLevel(const Character& character) const {
    int characterLevel = 0;

    for (int i = 0; i < character.getInventory().size(); ++i) {
        characterLevel += character.getInventory()[i].getDamage();
        characterLevel += character.getInventory()[i].getHitPoints();
    }
    return characterLevel;
}

Monster CaveFactory::findMatchingPowerLevel(int powerLevel) {
    int buffer = 0;
    while (powerLevel - buffer > 0) {
        for (int i = 0; i < allMonsters.size(); ++i) {
            if (allMonsters[i].getDamage() + allMonsters[i].getHitPoints() == powerLevel - buffer) {
                return allMonsters[i];
            }
        }
        buffer++;
    }
    return allMonsters[0];
}

Character CaveFactory::createEnemy(int characterLevel) {
    int randomIndex;
    std::vector<std::string> randomNames = {"Colin Jersey", "Galilea Mahoney", "Kamryn Sellers", "Mercy Gross", "Quinn Fleming", "Fatima Johnston", "Felix Landry", "Brynleigh Ryan", "Timothy Lozano", "Cecelia Nunez", "Caden Donaldson", "Natasha Sharp", "Royce Kane", "Ellianna Hansen", "Charlie Walton", "Scarlet Curry", "Briggs Neal", "Talia House", "Yehuda Patrick", "Lyra Lucas", "Chance Stark"};
    randomIndex = rand() % randomNames.size();

    Character enemy = Character(randomNames[randomIndex]);    
    characterLevel *= 0.8;
    int firstDesiredMonsterPowerLevel = characterLevel * 2/3;
    int secondDesiredMonsterPowerLevel = (characterLevel - firstDesiredMonsterPowerLevel) * 2/3;
    int thirdDesiredMonsterPowerLevel = characterLevel - firstDesiredMonsterPowerLevel - secondDesiredMonsterPowerLevel;

    enemy.addMonster(findMatchingPowerLevel(firstDesiredMonsterPowerLevel));
    if (characterLevel > 50) {
        enemy.addMonster(findMatchingPowerLevel(secondDesiredMonsterPowerLevel));
    }
    if (characterLevel > 90) {
        enemy.addMonster(findMatchingPowerLevel(thirdDesiredMonsterPowerLevel));
    }

    return enemy;
}

Item CaveFactory::clearReward() {
    int randomIndex;
    randomIndex = rand() % allItems.size();
    return allItems[randomIndex];
}

CaveFactory::~CaveFactory() {}
