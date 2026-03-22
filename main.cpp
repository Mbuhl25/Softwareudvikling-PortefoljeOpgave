#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <random>
#include "Character.h"
#include "Monster.h"
#include "AsciiPrinter.h"
#include "Monster.h"

int main() {
    bool playing = true;
    std::string characterName = "Johnny";
    Character player = Character(characterName);

    Monster Bat        = Monster("Benny Bat",          20,  15, "AsciiArt/Bat.txt");
    Monster Bee        = Monster("Buzzing Bee",        10,  20, "AsciiArt/Bee.txt");
    Monster Cat        = Monster("Clever Cat",         30,  25, "AsciiArt/Cat.txt");
    Monster Cockroach  = Monster("Creepy Cockroach",   15,  10, "AsciiArt/Cockroach.txt");
    Monster Cow        = Monster("oward Cow",         150,  35, "AsciiArt/Cow.txt");
    Monster Deer       = Monster("Dashing Deer",      120,  30, "AsciiArt/Deer.txt");
    Monster Duckling   = Monster("Dizzy Duckling",     15,   5, "AsciiArt/Duckling.txt");
    Monster Elephant   = Monster("Enormous Elephant", 200,  50, "AsciiArt/Elephant.txt");
    Monster Fish       = Monster("Flipping Fish",      20,  10, "AsciiArt/Fish.txt");
    Monster Frog       = Monster("Fierce Frog",        25,  15, "AsciiArt/Frog.txt");
    Monster Horse      = Monster("Hardy Horse",       160,  40, "AsciiArt/Horse.txt");
    Monster Mouse      = Monster("Mighty Mouse",       10,  12, "AsciiArt/Mouse.txt");
    Monster Owl        = Monster("Observant Owl",      35,  30, "AsciiArt/Owl.txt");
    Monster Penguin    = Monster("Punchy Penguin",     40,  25, "AsciiArt/Penguin.txt");
    Monster Porcupine  = Monster("Prickly Porcupine",  60,  35, "AsciiArt/Porcupine.txt");
    Monster Rabbit     = Monster("Raging Rabbit",      20,  15, "AsciiArt/Rabbit.txt");
    Monster Spider     = Monster("Savage Spider",      15,  45, "AsciiArt/Spider.txt");
    Monster Squirrel   = Monster("Sneaky Squirrel",    25,  20, "AsciiArt/Squirrel.txt");

    std::vector<Monster> allMonsters{Bat, Bee, Cat, Cockroach, Cow, Deer, Duckling, Elephant, Fish, Frog, Horse, Mouse, Owl, Penguin, Porcupine, Rabbit, Spider, Squirrel};
    std::vector<Monster> starterMonsters;
    for (int i = 0; i < 4; ++i) {
        std::random_device rd;
        std::mt19937 randomGenerator(rd());
        std::uniform_int_distribution<> randomMonsterNumber(0,allMonsters.size()-1);
        starterMonsters.push_back(allMonsters[randomMonsterNumber(randomGenerator)]);
    }

    AsciiPrinter screen = AsciiPrinter();

    while (true) {
        std::cout << "Choose your starter Monster: " << std::endl;
        screen.printInventory(starterMonsters);
        int numberChoice;
        std::cin >> numberChoice;
        if (numberChoice == 1 || numberChoice == 2 || numberChoice == 3 || numberChoice == 4) {
            if (!player.addMonster(starterMonsters[numberChoice-1])) {
                screen.printInventory(player.getInventory());
            }
            else {
                break;
            }
        }
        else {
            std::cout << "invalid input, try again" << std::endl;
        }
    }

    while (playing == true) {        
        std::cout << "Do you want to keep playing ( 1 )\nOr do you wish to exit the game ( 0 )" << std::endl;
        std::string answer = "";
        std::getline(std::cin, answer);

        if (answer == "0") {
            std::cout << "Thanks for playing\n" << std::endl;
            break;
        }
        else if (answer == "1") {
            std::cout << "Nu kæmper vi mod en fjende\n" << std::endl;
            screen.printFightScreen();
        }
        else {
            std::cout << "Invalid input!\n" << std::endl;
        }
    }
}