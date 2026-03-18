#include "Character.h"

Character::Character() {}

Character::Character(std::string _name) {
    name = _name;
}

std::string Character::getName() {
    return name;
}

void Character::setName(std::string _name) {
    name = _name;
}

Character::~Character() {}