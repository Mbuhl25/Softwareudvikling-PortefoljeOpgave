// Database Header file
#ifndef DATABASE_H
#define DATABASE_H

#include "Monster.h"
#include "Item.h"
#include "Character.h"

class database
{
public:
    database();
    int printCharacters();
    int getSavedCharactersAmount();
    Character loadCharacter(int);
    bool insertNewCharacter(Character);
    bool insertNewMonster(Character, Monster);
    bool insertNewItem(Character, Monster, Item);
    ~database();
private:
    int getCharacterID(Character);
    int getActiveMonsterID(int, Monster);
};
#endif