// Character Header file
#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>
#include <vector>
#include "Monster.h"
#pragma once

class Character {
    public:
        Character();
        Character(std::string);

        // Getters
        const std::string& getName() const;
        const std::vector<Monster>& getInventory() const;
        Monster& getChosenMonster();

        // Modifiers
        bool setChosenMonster(int index);
        bool addMonster(const Monster& monster);
        void removeMonster(int index);
        void setName(const std::string& name);


        ~Character();
    private:
        std::string name;
        std::vector<Monster> inventory;
        int activeMonster;
        int inventorySize;
};
#endif