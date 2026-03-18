// Monster Header file
#include <string>
#pragma once

class Monster {
    public:
        Monster();
        Monster(std::string, int, int);
        std::string getName();
        int getHitPoints();
        int getDamage();
        
        void setName(std::string);
        int takeDamage(int);
        ~Monster();
    private:
        std::string name;
        int hitPoints;
        int damage;
};