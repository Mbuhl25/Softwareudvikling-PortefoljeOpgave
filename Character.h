// Character Header file
#include <string>
#include <vector>
#include "Monster.h"
#pragma once

class Character {
    public:
        Character();
        Character(std::string);
        std::string getName();
        std::vector<Monster>& getInventory();

        bool addMonster(Monster);
        void removeMonster(int);
        void setName(std::string);
        ~Character();
    private:
        std::string name;
        std::vector<Monster> inventory;
};