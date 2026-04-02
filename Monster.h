// Monster Header file
#include <string>
#include <vector>
#pragma once

class Monster {
    public:
        Monster();
        Monster(std::string, int, int, std::string);

        // Getters
        const std::string& getName() const;
        int getHitPoints() const;
        int getDamage() const;
        const std::vector<std::string>& getAppearance() const;
        bool getStatus() const;
        // Modifiers
        void setName(std::string&);
        int takeDamage(int);
        ~Monster();
    private:
        std::string name;
        int hitPoints;
        int damage;
        std::vector<std::string> appearance;
        bool alive;
};