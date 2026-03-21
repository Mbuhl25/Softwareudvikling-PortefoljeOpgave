#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "Character.h"
#include "Monster.h"
#include "AsciiPrinter.h"
#include "Monster.h"

int main() {
    bool playing = true;
    std::string characterName = "Johnny";
    Character player = Character(characterName);

    Monster Rabbit = Monster("clapit rabbit", 10, 5, "AsciiArt/Rabbit.txt");
    Monster Deer = Monster("Deerio", 200, 15, "AsciiArt/Deer.txt");
    Monster Owl = Monster("Owlie Bowlie", 25, 30, "AsciiArt/Owl.txt");
    Monster Spider = Monster("SpiderMan", 25, 30, "AsciiArt/Spider.txt");
    Monster Cat = Monster("Catwoman", 25, 30, "AsciiArt/Cat.txt");

    AsciiPrinter screen = AsciiPrinter();
    screen.setMonsters(Deer.getAppearance(), Owl.getAppearance());

    if (not player.addMonster(Rabbit)) {
        screen.printInventory(player.getInventory());
    }
    if (not player.addMonster(Rabbit)) {
        screen.printInventory(player.getInventory());
    }
    if (not player.addMonster(Rabbit)) {
        screen.printInventory(player.getInventory());
    }
    if (not player.addMonster(Rabbit)) {
        screen.printInventory(player.getInventory());
    }
    if (not player.addMonster(Rabbit)) {
        screen.printInventory(player.getInventory());
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