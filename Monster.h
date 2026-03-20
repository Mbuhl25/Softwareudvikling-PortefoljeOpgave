// Monster Header file
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#pragma once

class Monster {
    public:
        Monster();
        Monster(std::string, int, int, std::string);
        std::string getName();
        int getHitPoints();
        int getDamage();
        std::vector<std::string> getAppearance();
        
        void setName(std::string);
        int takeDamage(int);
        ~Monster();
    private:
        std::string name;
        int hitPoints;
        int damage;
        std::vector<std::string> appearance;
};