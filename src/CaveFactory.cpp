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
    Monster("Dizzy Duckling",     15,   5, "../AsciiArt/Duckling.txt"),
    Monster("Creepy Cockroach",   10,  10, "../AsciiArt/Cockroach.txt"),
    Monster("Mighty Mouse",       10,  15, "../AsciiArt/Mouse.txt"),
    Monster("Flipping Fish",      20,  10, "../AsciiArt/Fish.txt"),
    Monster("Savage Spider",      15,  25, "../AsciiArt/Spider.txt"),
    Monster("Raging Rabbit",      20,  15, "../AsciiArt/Rabbit.txt"),
    Monster("Fierce Frog",        25,  15, "../AsciiArt/Frog.txt"),
    Monster("Buzzing Bee",        10,  20, "../AsciiArt/Bee.txt"),
    Monster("Benny Bat",          20,  15, "../AsciiArt/Bat.txt"),
    Monster("Sneaky Squirrel",    25,  20, "../AsciiArt/Squirrel.txt"),
    Monster("Punchy Penguin",     40,  25, "../AsciiArt/Penguin.txt"),
    Monster("Clever Cat",         30,  25, "../AsciiArt/Cat.txt"),
    Monster("Observant Owl",      35,  30, "../AsciiArt/Owl.txt"),
    Monster("Dashing Deer",      120,  30, "../AsciiArt/Deer.txt"),
    Monster("Prickly Porcupine",  60,  35, "../AsciiArt/Porcupine.txt"),
    Monster("oward Cow",         150,  35, "../AsciiArt/Cow.txt"),
    Monster("Hardy Horse",       160,  40, "../AsciiArt/Horse.txt"),
    Monster("Enormous Elephant", 200,  50, "../AsciiArt/Elephant.txt"),
    Monster("Enormous Elephant", 200, 150, "../AsciiArt/Dragon.txt"),
    };

    tier1Monsters = {
    Monster("Wiggly Worm",        5,    5, "../AsciiArt/Worm.txt"),
    Monster("Dizzy Duckling",     15,   5, "../AsciiArt/Duckling.txt"),
    Monster("Creepy Cockroach",   10,  10, "../AsciiArt/Cockroach.txt"),
    Monster("Mighty Mouse",       10,  15, "../AsciiArt/Mouse.txt"),
    Monster("Flipping Fish",      20,  10, "../AsciiArt/Fish.txt"),
    };
}

const std::vector<Monster>& CaveFactory::getMonsterList(int tier) const {
    if (tier == 0) {
        return allMonsters;
    } else if (tier == 1) {
        return tier1Monsters;
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

Character CaveFactory::createEnemy(int characterLevel) {
    int randomIndex;
    std::vector<std::string> randomNames = {"Colin Jersey", "Galilea Mahoney", "Kamryn Sellers", "Mercy Gross", "Quinn Fleming", "Fatima Johnston", "Felix Landry", "Brynleigh Ryan", "Timothy Lozano", "Cecelia Nunez", "Caden Donaldson", "Natasha Sharp", "Royce Kane", "Ellianna Hansen", "Charlie Walton", "Scarlet Curry", "Briggs Neal", "Talia House", "Yehuda Patrick", "Lyra Lucas", "Chance Stark"};
    randomIndex = rand() % randomNames.size();

    Character enemy = Character(randomNames[randomIndex]);

    enemy.addMonster(allMonsters[0]);

    return enemy;
}

CaveFactory::~CaveFactory() {}
