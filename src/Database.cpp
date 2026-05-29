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
            std::cout << tempCharacter.getInventory()[i].getName() << std::endl;
            if (tempCharacter.getInventory()[i].getName() == monsterName) {
                tempCharacter.getInventory()[i].addItem(itemName);
            }
        }
    }
    return tempCharacter;
}


database::~database() {}