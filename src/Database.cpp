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
    return tempCharacter;
}

database::~database() {}