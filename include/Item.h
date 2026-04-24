#ifndef ITEM_H
#define ITEM_H

#include <string>
#include "Monster.h"

class Item
{
public:
    Item(std::string, std::string);
    void setName(std::string);
    std::string getName();
    std::string getStatus();

    void useItem(Monster&);
    ~Item();
private:
    std::string name;
    std::string status;
    enum class ItemType {Bomb, FireBomb, Poison};
    ItemType itemEnum;
};

#endif