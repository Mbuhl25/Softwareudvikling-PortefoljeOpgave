#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <random>
#include <cstdlib>
#include <ctime>
#include "Character.h"
#include "Monster.h"
#include "AsciiPrinter.h"
#include "Monster.h"
#include "Item.h"
#include "CaveFactory.h"
#include "Database.h"

CaveFactory caveGenerator = CaveFactory();
AsciiPrinter screen = AsciiPrinter();
database db = database();

int getNumberInput(int lowerBound, int upperBound) {
    int numberChoice;
    while (true) {
        std::string line;
        std::getline(std::cin, line);
        std::stringstream ss(line);
        if (!(ss >> numberChoice)) {
            std::cout << "invalid input, pls enter a number\n";
            continue;
        }
        char extra;
        if (ss >> extra) {
            std::cout << "invalid input, no extra characters allowed\n";
            continue;
        }
        if (numberChoice >= lowerBound && numberChoice <= upperBound) {
            return numberChoice;
        }
        std::cout << "invalid range\n";
    }
}

void chooseMonster(Character& character, const std::vector<Monster>& monsterList, int possibilities) {
    // Generate a list of random monsters from the monsterList
    std::vector<Monster> possibilitiesMonsters;
    std::random_device rd;
    std::mt19937 randomGenerator(rd());
    std::uniform_int_distribution<> randomMonsterNumber(0,monsterList.size()-1);
    
    for (int i = 0; i < possibilities; ++i) {
        possibilitiesMonsters.push_back(monsterList[randomMonsterNumber(randomGenerator)]);
    }

    int numberChoice;
    while (true) {
        // If only one option is given, no choices are required, and the one monster is added to the inventory.
        if (possibilities == 1) {
            character.addMonster(possibilitiesMonsters[0]);
            break;
        }
        screen.printInventory(possibilitiesMonsters);
        numberChoice = getNumberInput(1, possibilities); 

        
        if (character.addMonster(possibilitiesMonsters[numberChoice-1])) {
            return;
        }
        else {
            while (true) {
                std::cout << "You already have " << character.getInventory().size() << " monsters. Choose one to replace: " << std::endl;
                screen.printInventory(character.getInventory());
                numberChoice = getNumberInput(1, character.getInventory().size() + 1);
                db.removeMonsterFromInventory(character, character.getInventory()[numberChoice-1]);
                character.removeMonster(numberChoice);
                return;
            }
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
    std::string name;
    std::getline(std::cin, name);
    Character newplayer = Character(name);
    std::cout << "Choose two Starter Monsters for " << newplayer.getName() << std::endl;
    chooseMonster(newplayer, caveGenerator.getMonsterList(1), 3);
    chooseMonster(newplayer, caveGenerator.getMonsterList(1), 3);
    db.insertNewCharacter(newplayer);
    return newplayer;
}

bool fightEnemy(Character& player) {
    Character enemy = caveGenerator.createEnemy(caveGenerator.EstimatePlayerLevel(player));
    std::cout << "You are now entering a cave, and here waits an opponent, " << enemy.getName()
    << ", Your opponent wishes to kill you,\nbe ready to fight her and her monsters to the death!\n" << std::endl;
    screen.printInventory(enemy.getInventory());

    std::cout << "Which of your Monsters should start the fight? " << std::endl;
    screen.printInventory(player.getInventory());

    // a loop to make sure, a correct input is given
    int numberChoice;
    player.setChosenMonster(getNumberInput(1, player.getInventory().size()));

    std::vector<Character*> fighters = {&player, &enemy};

    int randomTurn = randomTurnHandler();
    while (!enemy.getInventory().empty()) {
        // Logic if enemy monster dies
        if (enemy.getChosenMonster().getStatus() == "Fainted") {
            randomTurn = 2;
            screen.printFightScreen(player.getChosenMonster(), enemy.getChosenMonster(), randomTurn);
            numberChoice = getNumberInput(1, 2);
            switch (numberChoice){
                case 1:
                    // enemy.getChosenMonster().revive();
                    db.insertNewMonster(player, enemy.getChosenMonster());
                    if (player.addMonster(enemy.getChosenMonster())) {
                        enemy.removeMonster(1);
                        enemy.setChosenMonster(1);
                    }
                    else {
                        std::cout << "You already have " << player.getInventory().size() << " monsters. Choose one to replace: " << std::endl;
                        screen.printInventory(player.getInventory());
                        numberChoice = getNumberInput(1, player.getInventory().size() + 1);
                        db.removeMonsterFromInventory(player, player.getInventory()[numberChoice-1]);
                        player.removeMonster(numberChoice);
                        enemy.removeMonster(1);
                        enemy.setChosenMonster(1);
                    }
                    break;
                case 2:
                    enemy.removeMonster(1);
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
                return false;
            }
            std::cout << "Which of your Monsters should be swapped into the fight " << std::endl;
            screen.printInventory(player.getInventory());
            player.setChosenMonster(getNumberInput(1, player.getInventory().size()));
        }
        
        else if (randomTurn == 0) {
            screen.printFightScreen(player.getChosenMonster(), enemy.getChosenMonster(), randomTurn);
            numberChoice = getNumberInput(1, 3);
            switch (numberChoice){
                case 1:
                    fighters[!randomTurn]->getChosenMonster().takeDamage(fighters[randomTurn]->getChosenMonster().getDamage());
                    break;
                case 2:
                    std::cout << "Which of your Monsters should be swapped into the fight " << std::endl;
                    screen.printInventory(player.getInventory());
                    // a loop to make sure, a correct input is given
                    player.setChosenMonster(getNumberInput(1, player.getInventory().size()));
                    break;
                case 3:
                    if (player.getChosenMonster().getItemList().empty()) {
                        std::cout << "You don't have any items, so your monster attacks instead" << std::endl;
                        fighters[!randomTurn]->getChosenMonster().takeDamage(fighters[randomTurn]->getChosenMonster().getDamage());
                        break;
                    }
                    std::cout << "Choose an item to use:" << std::endl;
                    for (int i = 0; i < player.getChosenMonster().getItemList().size(); ++i) {
                        std::cout << "[" << i+1 << "]   " << player.getChosenMonster().getItemList()[i].getName() << std::endl;
                    }
                    numberChoice = getNumberInput(1, player.getChosenMonster().getItemList().size());
                    player.getChosenMonster().getItemList()[numberChoice-1].useItem(enemy.getChosenMonster());
            }
        } else if (randomTurn == 1) {
            int percentage;
            percentage = rand() % 100 + 1;

            // Apply status effects
            if (enemy.getChosenMonster().getStatus() == "Stunned") {
                enemy.getChosenMonster().setStatus("");
                randomTurn = !randomTurn;
                continue;
            }
            if (enemy.getChosenMonster().getStatus() == "Paralyzed") {
                if (percentage <= 30) {
                    randomTurn = !randomTurn;
                    continue;
                }
            }
            if (enemy.getChosenMonster().getStatus() == "Frozen") {
                if (enemy.getChosenMonster().getFrozenTimes() > 0) {
                    enemy.getChosenMonster().setFrozenTimes(enemy.getChosenMonster().getFrozenTimes() - 1);
                    randomTurn = !randomTurn;
                    continue;
                } else {
                    enemy.getChosenMonster().setStatus("");
                }
            }
            screen.printFightScreen(player.getChosenMonster(), enemy.getChosenMonster(), randomTurn);
            fighters[!randomTurn]->getChosenMonster().takeDamage(fighters[randomTurn]->getChosenMonster().getDamage());
            // Apply status effects
            if (enemy.getChosenMonster().getStatus() == "Curse") {
                enemy.getChosenMonster().takeDamage(5);
            }
            if (enemy.getChosenMonster().getStatus() == "Poisoned") {
                enemy.getChosenMonster().takeDamage(5);
            }
        }
        randomTurn = !randomTurn;
    }
    Item itemReward = caveGenerator.clearReward();
    std::cout << "\nAt the end of the cave you found the Item: " << itemReward.getName() << "." << std::endl;
    std::cout << "You can now give it to one of you Monsters: " << std::endl;
    screen.printInventory(player.getInventory());
    numberChoice = getNumberInput(1, player.getInventory().size());
    player.setChosenMonster(numberChoice);
    db.insertNewItem(player, player.getChosenMonster(), itemReward);
    player.getChosenMonster().addItem(itemReward);

    // revive fainted monsters
    for (int i = 1; i < player.getInventory().size()+1; ++i) {
        player.setChosenMonster(i);
        if (player.getChosenMonster().getStatus() == "Fainted") {
            player.getChosenMonster().revive();
        }
    }
    for (int i = 0; i < player.getInventory().size(); ++i) {
        player.getInventory()[i].revive();
    }
    return true;
}

int main() {
    std::srand(std::time(0));
    // Start of logic for the game
    std::cout << "---=== Animon - Not a rip-off of Pokimon ===--- " << std::endl;
    Character player = Character("");
    std::cout << "What do you want to do?\n [1] Create a new character\n [2] Load a character from the database" << std::endl;
    int numberChoice = getNumberInput(1, 2);
    switch (numberChoice)
    {
    case 1:
        player = createCharacter();
        break;
    case 2:
        std::cout << "\nChoose one of the characters from the database:" << std::endl;
        std::cout << "[0] Make a new Character" << std::endl;
        numberChoice = getNumberInput(0,db.printCharacters());
        player = db.loadCharacter(numberChoice);
        break;
    }
    while (true) {
        std::cout << "This is the main menu" << std::endl;
        if (player.getInventory().empty()) {
            std::cout << "Since you dont have a Character, you have to create one now" << std::endl;
            player = createCharacter();
        }
        // main loop of the game
        std::cout << "What do you want to do?\n [0] Load a previous character\n [1] Create a new character\n [2] Fight a monster\n [3] Check your inventory\n [4] exit the game" << std::endl;
        int numberChoice = getNumberInput(0, 4);
        switch (numberChoice) {
            case 0:
                std::cout << "current name: " << player.getName() << std::endl;
                std::cout << "Switching to load character\n" << std::endl;
                numberChoice = getNumberInput(0, db.printCharacters());
                player = db.loadCharacter(numberChoice);
                break;
            case 1:
                std::cout << "Switching to create character\n" << std::endl;
                player = createCharacter();
                break;
            case 2:
                std::cout << "Switching to fight\n" << std::endl;
                if (!fightEnemy(player)) {
                    player = createCharacter();
                }
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