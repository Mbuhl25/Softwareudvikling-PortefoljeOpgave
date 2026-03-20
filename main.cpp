#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "Character.h"
#include "Monster.h"
#include "AsciiPrinter.h"

int main() {
    bool playing = true;
    std::cout << std::setw(8) << " ---Launching Pokemon --- " << std::endl;
    std::cout  << " --Pls Create a Character " << std::endl;
    std::string characterName;
    std::getline(std::cin, characterName);
    Character player = Character(characterName);
    std::cout << "Created new Character called " << player.getName() << std::endl;

    Monster Rabbit = Monster("clapit rabbit", 10, 5, "AsciiArt/Rabbit.txt");
    Monster Deer = Monster("Deerio", 200, 15, "AsciiArt/Deer.txt");
    Monster Owl = Monster("Owlie Bowlie", 25, 30, "AsciiArt/Owl.txt");

    AsciiPrinter screen = AsciiPrinter();
    screen.updateMonsters(Deer.getAppearance(), Owl.getAppearance());

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
            screen.printScreen();
        }
        else {
            std::cout << "Invalid input!\n" << std::endl;
        }
    }
}