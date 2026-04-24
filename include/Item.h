#ifndef ITEM_H
#define ITEM_H

#include <string>

class Monster;

class Item
{
public:
    Item(std::string);
    std::string getName();
    void useItem(Monster&);
    ~Item();
private:
    std::string name;
    enum class ItemType {Bomb, FireBomb, ThunderBomb, Club, IceCubes, Curse, Poison};
    ItemType itemEnum;
};

#endif