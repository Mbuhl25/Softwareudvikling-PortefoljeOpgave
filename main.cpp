#include <iostream>
#include <string>

int main() {
    bool playing = true;
    std::cout << " ---Launching Pokemon --- " << std::endl;
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
        }
        else {
            std::cout << "Invalid input!\n" << std::endl;
        }
    }
}