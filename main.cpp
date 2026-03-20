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


    Monster Scorpion = Monster("Scorpion King", 5, 5);
    Scorpion.takeDamage(3);
    std::cout << Scorpion.getName() << " has this amount of HP: " << Scorpion.getHitPoints() << std::endl;

    AsciiPrinter screen = AsciiPrinter(" ", " ");

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