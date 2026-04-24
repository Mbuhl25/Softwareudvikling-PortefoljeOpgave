#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <random>
#include "Character.h"
#include "Monster.h"
#include "AsciiPrinter.h"
#include "Monster.h"
#include "Item.h"
#include "CaveFactory.h"

CaveFactory caveGenerator = CaveFactory();
AsciiPrinter screen = AsciiPrinter();

void chooseMonster(Character& character, const std::vector<Monster>& monsterList, int possibilities) {
    // Generate a list of random monsters from the monsterList
    std::vector<Monster> possibilitiesMonsters;
    std::random_device rd;
    std::mt19937 randomGenerator(rd());
    std::uniform_int_distribution<> randomMonsterNumber(0,monsterList.size()-1);
    
    for (int i = 0; i < possibilities; ++i) {
        possibilitiesMonsters.push_back(monsterList[randomMonsterNumber(randomGenerator)]);
    }

    while (true) {
        // If only one option is given, no choices are required, and the one monster is added to the inventory.
        if (possibilities == 1) {
            character.addMonster(possibilitiesMonsters[0]);
            break;
        }
        screen.printInventory(possibilitiesMonsters);
        int numberChoice;
        std::cin >> numberChoice;
        // Check for valid input
        if (numberChoice >= 1 && numberChoice <= possibilities) {
            if (character.addMonster(possibilitiesMonsters[numberChoice-1])) {
                return;
            }
            else {
                while (true) {
                    std::cout << "You already have " << character.getInventorySize() << " monsters. Choose one to replace: " << std::endl;
                    screen.printInventory(character.getInventory());
                    std::cin >> numberChoice;
                    if (numberChoice >= 1 && numberChoice <= character.getInventorySize() + 1) {
                        character.removeMonster(numberChoice-1);
                        return;
                    }
                    std::cout << "Invalid input, you have to choose a monster from 1 to " << character.getInventorySize() + 1 << std::endl;
                }
            }
        }
        // Error handling
        else {
            std::cout << "invalid input, the input must be between 1 and " << possibilities << std::endl;
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
        std::cout << "Choose two Starter Monsters for " << newplayer.getName() << std::endl;
        chooseMonster(newplayer, caveGenerator.getMonsterList(1), 3);
        chooseMonster(newplayer, caveGenerator.getMonsterList(1), 3);
        chooseMonster(newplayer, caveGenerator.getMonsterList(2), 3);
        return newplayer;
    }

void fightEnemy(Character& player) {
    Character enemy = caveGenerator.createEnemy(caveGenerator.EstimatePlayerLevel(player));
    std::cout << "You are now entering a cave, and here waits an opponent, " << enemy.getName()
    << ", Your opponent wishes to kill you,\nbe ready to fight her and her monsters to the death!\n" << std::endl;
    screen.printInventory(enemy.getInventory());

    std::cout << "Which of your Monsters should start the fight? " << std::endl;
    screen.printInventory(player.getInventory());

    // a loop to make sure, a correct input is given
    int numberChoice;
    do {
        std::cin >> numberChoice;
    } while (!player.setChosenMonster(numberChoice));

    std::vector<Character*> fighters = {&player, &enemy};

    int randomTurn = randomTurnHandler();
    while (!enemy.getInventory().empty()) {
        // Logic if enemy monster dies
        if (enemy.getChosenMonster().getStatus() == "Fainted") {
            randomTurn = 2;
            screen.printFightScreen(player.getChosenMonster(), enemy.getChosenMonster(), randomTurn);
            std::cin >> numberChoice;
            switch (numberChoice){
                case 1:
                    // enemy.getChosenMonster().revive();
                    if (player.addMonster(enemy.getChosenMonster())) {
                        enemy.removeMonster(0);
                        enemy.setChosenMonster(1);
                    }
                    else {
                        while (true) {
                            std::cout << "You already have " << player.getInventorySize() << " monsters. Choose one to replace: " << std::endl;
                            screen.printInventory(player.getInventory());
                            std::cin >> numberChoice;
                            if (numberChoice >= 1 && numberChoice <= player.getInventorySize() + 1) {
                                player.removeMonster(numberChoice-1);
                                break;
                            }
                            std::cout << "Invalid input, you have to choose a monster from 1 to " << player.getInventorySize() + 1 << std::endl;
                        }
                        enemy.removeMonster(0);
                        enemy.setChosenMonster(1);
                    }
                    break;
                case 2:
                    enemy.removeMonster(0);
                    if (enemy.getInventory().size() > 1) {
                        enemy.setChosenMonster(1);
                    }
                    break;
            }
        // Logic if player monster dies
        } else if (player.getChosenMonster().getStatus() == "Fainted") {
            std::cout << "Your Monster just died" << std::endl;
            int aliveMonsters = 0;
            for (int i = 0; i < player.getInventory().size(); ++i) {
                if (player.getInventory()[i].getStatus() != "Fainted") {
                    aliveMonsters += 1;
                }
            }
            if (aliveMonsters == 0) {
                std::cout << "You have lost all of you Monsters, and your character is dead\n" << std::endl;
                break;
            }
            std::cout << "Which of your Monsters should be swapped into the fight " << std::endl;
            screen.printInventory(player.getInventory());
            // a loop to make sure, a correct input is given
            int numberChoice;
            do {
                std::cin >> numberChoice;
            } while (!player.setChosenMonster(numberChoice));
        }
        
        else if (randomTurn == 0) {
            screen.printFightScreen(player.getChosenMonster(), enemy.getChosenMonster(), randomTurn);
            std::cin >> numberChoice;
            switch (numberChoice){
                case 1:
                    fighters[!randomTurn]->getChosenMonster().takeDamage(fighters[randomTurn]->getChosenMonster().getDamage());
                    break;
                case 2:
                    std::cout << "Which of your Monsters should be swapped into the fight " << std::endl;
                    screen.printInventory(player.getInventory());
                    // a loop to make sure, a correct input is given
                    int numberChoice;
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
    // revive fainted monsters
    for (int i = 1; i < player.getInventory().size(); ++i) {
        player.setChosenMonster(i);
        if (player.getChosenMonster().getStatus() == "Fainted") {
            player.getChosenMonster().revive();
        }
    }
}

int main() {
    // Start of logic for the game
    std::cout << "---=== Animon - Not a rip-off of Pokimon ===--- " << std::endl;
    Character player = Character("");
    while (true) {
        std::cout << "This is the main menu" << std::endl;
        if (player.getInventory().empty()) {
            std::cout << "Since you dont have a Character, you have to create one now" << std::endl;
            player = createCharacter();
        }
        // main loop of the game
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