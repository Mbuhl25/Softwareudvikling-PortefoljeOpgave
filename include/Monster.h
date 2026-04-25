// Monster Header file
#ifndef MONSTER_H
#define MONSTER_H

#include <string>
#include <vector>
#include "Item.h"

class Monster {
    public:
        Monster();
        Monster(std::string, int, int, std::string);

        // Getters
        const std::string& getName() const;
        int getHitPoints() const;
        int getMaxHitPoints() const;
        int getDamage() const;
        const std::vector<std::string>& getAppearance() const;
        std::string getStatus() const;
        std::vector<Item> getItemList() const;
        // Modifiers
        void setName(std::string&);
        void setStatus(std::string);
        int takeDamage(int);
        int revive();
        void addItem(Item);
        ~Monster();
    private:
        std::string name;
        int hitPoints;
        int maxHitPoints;
        int damage;
        std::vector<std::string> appearance;
        std::string status;

        std::vector<Item> itemList;
};
#endif