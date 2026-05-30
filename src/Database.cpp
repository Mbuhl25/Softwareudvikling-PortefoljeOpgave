#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include <string>
#include <iostream>

#include "Database.h"

database::database() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("animonDatabase.db");

    if (!db.open()) {
        qDebug() << "Failed to open database";
    }
}

int database::printCharacters() {
    QSqlQuery query;
    query.exec("SELECT * FROM character");
    while (query.next()) {
        int number = query.value(0).toInt();
        std::string name = query.value(1).toString().toStdString() ;
        std::cout << "[" << number << "] " << name << std::endl;
        }
    // qDebug() << "Finished";
    return getSavedCharactersAmount();
}

int database::getSavedCharactersAmount() {
    QSqlQuery query;
    query.exec("SELECT COUNT(*) FROM character");
    int amount = 0;
    if (query.next()) {
        amount = query.value(0).toInt();
    }
    return amount;
    }


Character database::loadCharacter(int input) {
    QSqlQuery query;

    query.prepare(
        "SELECT * FROM character WHERE character_id = :id"
    );

    query.bindValue(":id", input);
    query.exec();

    std::string name = "";
    if (query.next()) {
        name = query.value(1).toString().toStdString();
    }
    

    Character tempCharacter = Character(name);
    
    QSqlQuery addCharacter;
    addCharacter.prepare("SELECT "
    "    monster.monster_name, "
    "    monster.monster_maxhp, "
    "    monster.monster_damage, "
    "    monster.monster_ascii "
    "FROM character "
    "JOIN character_inventory "
    "    ON character.character_id = character_inventory.character_id "
    "JOIN active_monster "
    "    ON character_inventory.active_monster_id = active_monster.active_monster_id "
    "JOIN monster "
    "    ON active_monster.monster_id = monster.monster_id "
    "WHERE character.character_id = ? "
    );

    addCharacter.addBindValue(input);
    addCharacter.exec();

    while (addCharacter.next()) {
        std::string name = addCharacter.value(0).toString().toStdString();
        int maxHP = addCharacter.value(1).toInt();
        int damage = addCharacter.value(2).toInt();
        std::string ascii = addCharacter.value(3).toString().toStdString();
        Monster tempMonster = Monster(name, maxHP, damage, ascii);
        tempCharacter.addMonster(tempMonster);
    }

    QSqlQuery addItem;
    addItem.prepare("SELECT "
    "    monster.monster_name, "
    "    item.item_name "
    "FROM character "
    "JOIN character_inventory "
    "    ON character.character_id = character_inventory.character_id "
    "JOIN active_monster "
    "    ON character_inventory.active_monster_id = active_monster.active_monster_id "
    "JOIN monster "
    "    ON monster.monster_id = active_monster.monster_id "
    "JOIN monster_inventory "
    "    ON active_monster.active_monster_id = monster_inventory.active_monster_id "
    "JOIN item "
    "    ON monster_inventory.item_id = item.item_id "
    "WHERE character.character_id = ? "
    );

    addItem.addBindValue(input);
    addItem.exec();

    while (addItem.next()) {
        std::string monsterName = addItem.value(0).toString().toStdString();
        std::string itemName = addItem.value(1).toString().toStdString();
        for (int i = 0; i < tempCharacter.getInventory().size(); ++i) {
            if (tempCharacter.getInventory()[i].getName() == monsterName) {
                tempCharacter.getInventory()[i].addItem(itemName);
            }
        }
    }
    return tempCharacter;
}

int database::getCharacterID(Character tempCharacter) {
    QSqlQuery getCharacter;
    getCharacter.prepare("SELECT character_id "
        "FROM character "
        "WHERE character_name = ?");
    getCharacter.addBindValue(QString::fromStdString(tempCharacter.getName()));
    if (!getCharacter.exec()) {
        std::cout << "FUCK 1" << std::endl;
        exit(1);
    }
    int characterID = 0;
    if (getCharacter.next()) {
        characterID = getCharacter.value(0).toInt();
    } else {std::cout << "FUCK 2" << std::endl; exit(1); }
    return characterID;
}

int database::getActiveMonsterID(int characterID, Monster tempMonster) {
    QSqlQuery getActiveMonsterID;
    getActiveMonsterID.prepare("SELECT "
                                "active_monster.active_monster_id, "
                                "monster.monster_name "
                            "FROM active_monster "
                            "JOIN monster "
                                "ON monster.monster_id = active_monster.monster_id "
                            "JOIN character_inventory "
                                "ON character_inventory.active_monster_id = active_monster.active_monster_id "
                            "WHERE character_inventory.character_id = ? "
                            "AND monster.monster_name = ? " 
                        "LIMIT 1");

    
    getActiveMonsterID.addBindValue(characterID);
    getActiveMonsterID.addBindValue(QString::fromStdString(tempMonster.getName()));
    
    if (!getActiveMonsterID.exec()) {
        std::cout << "FUCK 3" << std::endl;
        exit(1);
    }
    int activeMonsterID = 0;
    if (getActiveMonsterID.next()) {
        activeMonsterID = getActiveMonsterID.value(0).toInt();
    } else {std::cout << "FUCK 4" << std::endl; exit(1);}
    return activeMonsterID;
}

bool insertItem(int activeMonsterID, Item tempItem) {
    QSqlQuery getItem;
    getItem.prepare("SELECT item_id FROM item WHERE item_name = ?");
    getItem.addBindValue(QString::fromStdString(tempItem.getName()));

    if (!getItem.exec()) {return false;}
    int itemID = 0;
    if (getItem.next()) {
        itemID = getItem.value(0).toInt();
    } else {return false;}
    QSqlQuery insertItem;
    insertItem.prepare(
        "INSERT INTO monster_inventory (active_monster_id, item_id) "
        "VALUES (?, ?)"
    );
    insertItem.addBindValue(activeMonsterID);
    insertItem.addBindValue(itemID);
    if (!insertItem.exec()) {return false;}
    return true;
}

bool insertMonster(int characterID, Monster tempMonster) {
    // get monster
    QSqlQuery getMonster;
    getMonster.prepare("SELECT monster_id "
        "FROM monster "
        "WHERE monster_name = ?");
    getMonster.addBindValue(QString::fromStdString(tempMonster.getName()));
    getMonster.exec();
    int monsterID = 0;
    if (getMonster.next()) {
        monsterID = getMonster.value(0).toInt();
    } else {return false; }

    // Insert active_monster
    QSqlQuery insertActiveMonster;
    insertActiveMonster.prepare("INSERT INTO active_monster (monster_id) "
                "VALUES (?)");
    insertActiveMonster.addBindValue(monsterID);
    if (!insertActiveMonster.exec()) {
        return false;
    }
    int activeMonsterID = insertActiveMonster.lastInsertId().toInt();

    // inset into inventory
    QSqlQuery insertInventory;
    insertInventory.prepare("INSERT INTO character_inventory (character_id, active_monster_id) "
                "VALUES (?, ?)");
    insertInventory.addBindValue(characterID);
    insertInventory.addBindValue(activeMonsterID);
    if (!insertInventory.exec()) {
        return false;
    }

    // Insert Items
    for (int i = 0; i < tempMonster.getItemList().size(); ++i) {
        if(!insertItem(activeMonsterID, tempMonster.getItemList()[i])) {
            return false;
        }
    }
    return true;
}

bool database::insertNewCharacter(Character tempCharacter) {
    QSqlQuery insertCharacter;

    // Insert character
    insertCharacter.prepare("INSERT INTO character (character_name) "
                "VALUES (?)");
    insertCharacter.addBindValue(QString::fromStdString(tempCharacter.getName()));
    if (!insertCharacter.exec()) {
        return false;
    }
    int characterID = insertCharacter.lastInsertId().toInt();

    // Insert monsters
    for (int i = 0; i < tempCharacter.getInventory().size(); ++i) {
        if (!insertMonster(characterID, tempCharacter.getInventory()[i])) {
            return false;
        }
    }
    return true;
}

bool database::insertNewMonster(Character tempCharacter, Monster tempMonster) {
    int characterID = getCharacterID(tempCharacter);
    if (!insertMonster(characterID, tempMonster)) {
        return false;
    }
    return true;
}


bool database::insertNewItem(Character tempCharacter, Monster tempMonster, Item tempItem) {
    int characterID = getCharacterID(tempCharacter);
    int activeMonsterID = getActiveMonsterID(characterID, tempMonster);
    if (!insertItem(activeMonsterID, tempItem)) {
        return false;
    }
    return true;
}

database::~database() {}