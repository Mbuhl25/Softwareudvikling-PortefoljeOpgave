#include <QCoreApplication>
#include <QtSql>
#include <QSqlDatabase>
#include "Database.h"

database::database() {}

int database::querything(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("testing.db");
    db.open();
    QSqlQuery query;
    query.exec("SELECT * FROM monster");
    while (query.next()) {
        QString name = query.value(1).toString();
        qDebug() << name;
        }
    // qDebug() << "Finished";
    return 1;
}

database::~database() {}