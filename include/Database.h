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
    int displayCharacters();
    int getSavedCharactersAmount();
    Character loadCharacter(int);
    ~database();
private:
    
};
#endif