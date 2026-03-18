// Character Header file
#include <string>
#pragma once

class Character {
    public:
        Character();
        Character(std::string);
        std::string getName();
        void setName(std::string);
        ~Character();
    private:
        std::string name;
};