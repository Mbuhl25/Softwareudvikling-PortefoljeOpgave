#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <random>
#include "Character.h"
#include "Monster.h"
#include "AsciiPrinter.h"
#include "Monster.h"

void chooseMonster(Character& character, std::vector<Monster>& monsterList, AsciiPrinter& printer, int possibilities) {
    std::vector<Monster> possibilitiesMonsters;
    std::random_device rd;
    std::mt19937 randomGenerator(rd());
    std::uniform_int_distribution<> randomMonsterNumber(0,monsterList.size()-1);
    
    for (int i = 0; i < possibilities; ++i) {
        
        possibilitiesMonsters.push_back(monsterList[randomMonsterNumber(randomGenerator)]);
    }
    while (true) {
        if (possibilities == 1) {
            character.addMonster(possibilitiesMonsters[0]);
            break;
        }
        
        printer.printInventory(possibilitiesMonsters);
        int numberChoice;
        std::cin >> numberChoice;
        if (numberChoice >= 1 && numberChoice <= possibilities) {
            if (character.addMonster(possibilitiesMonsters[numberChoice-1])) {
                break;
            }
            else {
                std::cout << "You already have 4 monsters. Choose one to replace: " << std::endl;
                printer.printInventory(character.getInventory());
                std::cin >> numberChoice;
                character.removeMonster(numberChoice);
                break;
            }
        }
        else {
            std::cout << "invalid input, try again" << std::endl;
        }
    }
}

int randomTurnHandler() {
    std::random_device rd;
    std::mt19937 randomGenerator(rd());
    std::uniform_int_distribution<> fiftyFiftyChance(0,1);
    return fiftyFiftyChance(randomGenerator);
}


int main() {
    bool playing = true;
    Character player = Character("Johnny");
    Character enemy = Character("Cliff");

    Monster Worm       = Monster("Wiggly Worm",        5,    5, "AsciiArt/Worm.txt");
    Monster Duckling   = Monster("Dizzy Duckling",     15,   5, "AsciiArt/Duckling.txt");
    Monster Cockroach  = Monster("Creepy Cockroach",   10,  10, "AsciiArt/Cockroach.txt");
    Monster Mouse      = Monster("Mighty Mouse",       10,  15, "AsciiArt/Mouse.txt");
    Monster Fish       = Monster("Flipping Fish",      20,  10, "AsciiArt/Fish.txt");
    Monster Spider     = Monster("Savage Spider",      15,  25, "AsciiArt/Spider.txt");
    Monster Rabbit     = Monster("Raging Rabbit",      20,  15, "AsciiArt/Rabbit.txt");
    Monster Frog       = Monster("Fierce Frog",        25,  15, "AsciiArt/Frog.txt");
    Monster Bee        = Monster("Buzzing Bee",        10,  20, "AsciiArt/Bee.txt");
    Monster Bat        = Monster("Benny Bat",          20,  15, "AsciiArt/Bat.txt");
    Monster Squirrel   = Monster("Sneaky Squirrel",    25,  20, "AsciiArt/Squirrel.txt");   
    Monster Penguin    = Monster("Punchy Penguin",     40,  25, "AsciiArt/Penguin.txt");    
    Monster Cat        = Monster("Clever Cat",         30,  25, "AsciiArt/Cat.txt");
    Monster Owl        = Monster("Observant Owl",      35,  30, "AsciiArt/Owl.txt");
    Monster Deer       = Monster("Dashing Deer",      120,  30, "AsciiArt/Deer.txt");
    Monster Porcupine  = Monster("Prickly Porcupine",  60,  35, "AsciiArt/Porcupine.txt");
    Monster Cow        = Monster("oward Cow",         150,  35, "AsciiArt/Cow.txt");
    Monster Horse      = Monster("Hardy Horse",       160,  40, "AsciiArt/Horse.txt");
    Monster Elephant   = Monster("Enormous Elephant", 200,  50, "AsciiArt/Elephant.txt");

    std::vector<Monster> allMonsters{Bat, Bee, Cat, Cockroach, Cow, 
                                    Deer, Duckling, Elephant, Fish,
                                    Frog, Horse, Mouse, Owl, Penguin,
                                    Porcupine, Rabbit, Spider, Squirrel};
    std::vector<Monster> tier1Monsters{Worm, Duckling, Cockroach, Mouse, Fish, Spider};
    

    AsciiPrinter screen = AsciiPrinter();
    std::cout << "Choose your 2 first starter Monsters: " << std::endl;
    chooseMonster(player, tier1Monsters, screen, 3);
//    chooseMonster(player, tier1Monsters, screen, 3);

    while (true){
        std::cout << "Entering Battle now: " << std::endl;
        std::cout << "Choose your opponent: " << std::endl;
        std::cout << enemy.getInventory().size() << std::endl;
        while (enemy.getInventory().size() > 0) {enemy.removeMonster(1);}
        chooseMonster(enemy, tier1Monsters, screen, 3);
        
        std::cout << "Which of your Monsters should start the fight? " << std::endl;
        screen.printInventory(player.getInventory());
        int numberChoice;
        std::cin >> numberChoice;
        player.setChosenMonster(numberChoice);

        std::vector<Character*> fighters = {&player, &enemy};
        
        screen.setMonsters(player.getChosenMonster().getAppearance(), enemy.getChosenMonster().getAppearance());

        screen.printFightScreen(fighters[randomTurnHandler()]->getChosenMonster().getName());


        std::cin >> numberChoice;
    }

}