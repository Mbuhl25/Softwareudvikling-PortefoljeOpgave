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
    bool removeMonsterFromInventory(Character, Monster);
    bool insertFightStats(Character, Monster, Item, int);
    int amountOfKills(Character);
    std::pair<std::vector<std::string>, std::vector<int>> favouriteMonsters(Character);
    std::pair<std::vector<std::string>, std::vector<int>> favouriteItems(Character);
    std::pair<std::vector<std::string>, std::vector<int>> favouriteUsedItem(Character);
    ~database();
private:
    int getCharacterID(Character);
    int getActiveMonsterID(int, Monster);
    int getItemID(Item);
    int getMonsterID(int);
};
#endif