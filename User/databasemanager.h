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

    Q_INVOKABLE void generateTables();
    Q_INVOKABLE void insertPerson(const int index, const Person& member);
    Q_INVOKABLE void insertProject(const int index, const Project& project, const int memberId);
    Q_INVOKABLE void updatePerson(const int index, const Person& member);

    QVector<Person> selectData();

signals:

private:
    QSqlDatabase db;
    explicit DatabaseManager();
    DatabaseManager(QSharedPointer<SimpleSwitchReplica> ptr);

};

#endif // DATABASEMANAGER_H
