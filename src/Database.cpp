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

int database::displayCharacters() {
    QSqlQuery query;
    query.exec("SELECT * FROM character");
    while (query.next()) {
        int number = query.value(0).toInt();
        std::string name = query.value(1).toString().toStdString() ;
        std::cout << "[" << number << "] " << name << std::endl;
        }
    // qDebug() << "Finished";
    return 1;
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

    query.prepare(R"(
    SELECT
        monster.monster_name,
        monster.monster_maxhp,
        monster.monster_damage,
        monster.monster_ascii
    FROM character
    JOIN character_inventory
        ON character.character_id = character_inventory.character_id
    JOIN active_monster
        ON character_inventory.active_monster_id = active_monster.active_monster_id
    JOIN monster
        ON active_monster.monster_id = monster.monster_id
    WHERE character.character_id = :id
    )");

    query.bindValue(":id", input);
    query.exec();

    while (query.next()) {
        std::string name = query.value(0).toString().toStdString();
        int maxHP = query.value(1).toInt();
        int damage = query.value(2).toInt();
        std::string ascii = query.value(3).toString().toStdString();
        Monster tempMonster = Monster(name, maxHP, damage, ascii);
        tempCharacter.addMonster(tempMonster);
    }


    query.prepare(R"(
    SELECT 
        monster.monster_name,
        item.item_name
    FROM character
    JOIN character_inventory
        ON character.character_id = character_inventory.character_id
    JOIN active_monster
        ON character_inventory.active_monster_id = active_monster.active_monster_id
    JOIN monster
        ON monster.monster_id = active_monster.monster_id
    JOIN monster_inventory
        ON active_monster.active_monster_id = monster_inventory.active_monster_id
    JOIN item
        ON monster_inventory.item_id = item.item_id
    WHERE character.character_id = 1;
    )");

    query.bindValue(":id", input);
    query.exec();

    while (query.next()) {
        std::string monsterName = query.value(0).toString().toStdString();
        std::string itemName = query.value(1).toString().toStdString();
        for (int i = 0; i < tempCharacter.getInventory().size(); ++i) {
            if (tempCharacter.getInventory()[i].getName() == monsterName) {
                tempCharacter.getInventory()[i].addItem(itemName);
            }
        }
    }
    return tempCharacter;
}

bool database::insertCharacter(Character saveCharacter) {
    QSqlQuery insertCharacter;

    // Insert character
    insertCharacter.prepare("INSERT INTO character (character_name) "
                "VALUES (?)");
    insertCharacter.addBindValue(QString::fromStdString(saveCharacter.getName()));
    if (!insertCharacter.exec()) {
        return false;
    }
    int characterID = insertCharacter.lastInsertId().toInt();

    // Insert monsters
    for (int i = 0; i < saveCharacter.getInventory().size(); ++i) {
        QSqlQuery getMonster;
        getMonster.prepare("SELECT monster_id "
            "FROM monster "
            "WHERE monster_name = ?");
        getMonster.addBindValue(QString::fromStdString(saveCharacter.getInventory()[i].getName()));
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

        QSqlQuery insertInventory;
        insertInventory.prepare("INSERT INTO character_inventory (character_id, active_monster_id) "
                    "VALUES (?, ?)");
        insertInventory.addBindValue(characterID);
        insertInventory.addBindValue(activeMonsterID);
        if (!insertInventory.exec()) {
            return false;
        }

        // Insert Items
        for (int j = 0; j < saveCharacter.getInventory()[i].getItemList().size(); ++j) {
            QSqlQuery getItem;
            getItem.prepare("SELECT item_id "
                "FROM item "
                "WHERE item_name = ?");
            getItem.addBindValue(QString::fromStdString(saveCharacter.getInventory()[i].getItemList()[j].getName()));
            getItem.exec();
            int itemID = 0;
            if (getItem.next()) {
                itemID = getItem.value(0).toInt();
            } else {return false; }

            QSqlQuery insertItem;
            insertItem.prepare("INSERT INTO monster_inventory (active_monster_id, item_id) "
                        "VALUES (?, ?)");
            insertItem.addBindValue(activeMonsterID);
            insertItem.addBindValue(itemID);
            if (!insertItem.exec()) {
                return false;
            }
        }
    }
    return true;
}

database::~database() {}