#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <random>
#include "Character.h"
#include "Monster.h"
#include "AsciiPrinter.h"
#include "Monster.h"


// Initialize an object for every monster
Monster Worm       = Monster("Wiggly Worm",        5,    5, "./AsciiArt/Worm.txt");
Monster Duckling   = Monster("Dizzy Duckling",     15,   5, "./AsciiArt/Duckling.txt");
Monster Cockroach  = Monster("Creepy Cockroach",   10,  10, "./AsciiArt/Cockroach.txt");
Monster Mouse      = Monster("Mighty Mouse",       10,  15, "./AsciiArt/Mouse.txt");
Monster Fish       = Monster("Flipping Fish",      20,  10, "./AsciiArt/Fish.txt");
Monster Spider     = Monster("Savage Spider",      15,  25, "./AsciiArt/Spider.txt");
Monster Rabbit     = Monster("Raging Rabbit",      20,  15, "./AsciiArt/Rabbit.txt");
Monster Frog       = Monster("Fierce Frog",        25,  15, "./AsciiArt/Frog.txt");
Monster Bee        = Monster("Buzzing Bee",        10,  20, "./AsciiArt/Bee.txt");
Monster Bat        = Monster("Benny Bat",          20,  15, "./AsciiArt/Bat.txt");
Monster Squirrel   = Monster("Sneaky Squirrel",    25,  20, "./AsciiArt/Squirrel.txt");   
Monster Penguin    = Monster("Punchy Penguin",     40,  25, "./AsciiArt/Penguin.txt");    
Monster Cat        = Monster("Clever Cat",         30,  25, "./AsciiArt/Cat.txt");
Monster Owl        = Monster("Observant Owl",      35,  30, "./AsciiArt/Owl.txt");
Monster Deer       = Monster("Dashing Deer",      120,  30, "./AsciiArt/Deer.txt");
Monster Porcupine  = Monster("Prickly Porcupine",  60,  35, "./AsciiArt/Porcupine.txt");
Monster Cow        = Monster("oward Cow",         150,  35, "./AsciiArt/Cow.txt");
Monster Horse      = Monster("Hardy Horse",       160,  40, "./AsciiArt/Horse.txt");
Monster Elephant   = Monster("Enormous Elephant", 200,  50, "./AsciiArt/Elephant.txt");

// Make list that works for different categories (all, weak, strong)
std::vector<Monster> allMonsters{Bat, Bee, Cat, Cockroach, Cow, 
                                Deer, Duckling, Elephant, Fish,
                                Frog, Horse, Mouse, Owl, Penguin,
                                Porcupine, Rabbit, Spider, Squirrel};
std::vector<Monster> tier1Monsters{Worm, Duckling, Cockroach, Mouse, Fish};

AsciiPrinter screen = AsciiPrinter();

void chooseMonster(Character& character, std::vector<Monster>& monsterList, int possibilities) {
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
        
        screen.printInventory(possibilitiesMonsters);
        int numberChoice;
        std::cin >> numberChoice;
        if (numberChoice >= 1 && numberChoice <= possibilities) {
            if (character.addMonster(possibilitiesMonsters[numberChoice-1])) {
                break;
            }
            else {
                std::cout << "You already have 4 monsters. Choose one to replace: " << std::endl;
                screen.printInventory(character.getInventory());
                std::cin >> numberChoice;
                character.removeMonster(numberChoice);
                break;
            }
        }
        else {
            std::cout << "invalid input, try again" << std::endl;
            std::cin >> numberChoice;
        }
    }
}

int randomTurnHandler() {
    std::random_device rd;
    std::mt19937 randomGenerator(rd());
    std::uniform_int_distribution<> fiftyFiftyChance(0,1);
    return fiftyFiftyChance(randomGenerator);
}

    Character createCharacter() {
        std::cout << "Input the name of your new character: ";
        std::string input;
        std::cin >> input;
        Character newplayer = Character(input);
        std::cout << "Choose the Starter Monster for " << newplayer.getName() << std::endl;
        chooseMonster(newplayer, tier1Monsters, 3);
        newplayer.addMonster(Elephant);
        return newplayer;
    }

void fightEnemy(Character& player) {
    Character enemy = Character("Cliff");
    std::cout << "Choose the monster of " << enemy.getName() << ", your opponent: " << std::endl;
    chooseMonster(enemy, tier1Monsters, 3);

    if (player.getInventory().size() == 0){ return; }
    std::cout << "Which of your Monsters should start the fight? " << std::endl;
    screen.printInventory(player.getInventory());

    // a loop to make sure, a correct input is given
    int numberChoice;
    do {
        std::cin >> numberChoice;
    } while (!player.setChosenMonster(numberChoice));

    std::vector<Character*> fighters = {&player, &enemy};

    int randomTurn = randomTurnHandler();

    while (player.getChosenMonster().getHitPoints() > 0 && enemy.getChosenMonster().getHitPoints() > 0) {
        if (randomTurn == 0) {
            screen.printFightScreen(player.getChosenMonster(), enemy.getChosenMonster(), randomTurn);
            std::cin >> numberChoice;
            switch (numberChoice){
                case 1:
                    fighters[!randomTurn]->getChosenMonster().takeDamage(fighters[randomTurn]->getChosenMonster().getDamage());
                    break;
                case 2:
                    do {
                        std::cin >> numberChoice;
                    } while (!player.setChosenMonster(numberChoice));
                    break;
            }
        } else if (randomTurn == 1) {
            screen.printFightScreen(player.getChosenMonster(), enemy.getChosenMonster(), randomTurn);
            fighters[!randomTurn]->getChosenMonster().takeDamage(fighters[randomTurn]->getChosenMonster().getDamage());
        }
        randomTurn = !randomTurn;
    }



    for (int i = 0; i < player.getInventory().size(); ++i) {
        if (!player.getInventory()[i].getStatus()) {
            std::cout << player.getChosenMonster().getStatus() << std::endl;
            player.removeMonster(i+1);
        }
    }
}

int main() {
    // Start of logic for the game
    std::cout << "---=== Animon - Not a rip-off of Pokimon ===--- " << std::endl;
    Character player = Character("");
    while (true) {
        std::cout << "This is the main menu" << std::endl;
        if (player.getName() == "") {
            std::cout << "Since you dont have a Character yet, you have to create one now" << std::endl;
            player = createCharacter();
        }

        std::cout << "What do you want to do?\n [1] Create a new character\n [2] Fight a monster\n [3] Check your inventory\n [4] exit the game" << std::endl;
        int numberChoice = 0;
        if (numberChoice < 1 || numberChoice > 4) {
            std::cin >> numberChoice;
        }
        switch (numberChoice) {
            case 1:
                std::cout << "Switching to create character\n" << std::endl;
                player = createCharacter();
                break;
            case 2:
                std::cout << "Switching to fight\n" << std::endl;
                fightEnemy(player);
                break;
            case 3:
                std::cout << "Checking inventory\n" << std::endl;
                screen.printInventory(player.getInventory());
                break;
            case 4:
                std::cout << "Exiting the game\n" << std::endl;
                exit(0);
        }
    }
}