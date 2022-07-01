#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QDebug>
#include <QSqlQuery>
#include "rep_SimpleSwitch_replica.h"

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    static DatabaseManager &instance();
    ~DatabaseManager() {
        qDebug() << "Database die";
    }

    //prohibit copying object
    DatabaseManager(const DatabaseManager &) = delete;
    DatabaseManager & operator = (const DatabaseManager &) = delete;

    void generateTables();
    void insertPerson(const int index, const Person& member);
    void insertProject(const int index, const Project& project);

signals:

private:
    QSqlDatabase db;
    explicit DatabaseManager(QObject *parent = nullptr);

};

#endif // DATABASEMANAGER_H
