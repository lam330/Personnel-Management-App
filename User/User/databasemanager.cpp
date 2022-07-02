#include "databasemanager.h"
#include "client.h"

DatabaseManager &DatabaseManager::instance()
{
    static DatabaseManager database;
    return database;
}

DatabaseManager::DatabaseManager()
{
    //Create file db
    QString path = "E:/Qt_again/MyProject/My-project-IPC-Thread-SQlite-Networking/Database/database17.db";
    db = QSqlDatabase::addDatabase("QSQLITE");
    qDebug() << "The connection name: " << QSqlDatabase::connectionNames();
    db.setDatabaseName(path);
    bool test = db.open();

    if(test) {
        qDebug() << "Opened data file";
    }
    //generateTables();
}

DatabaseManager::DatabaseManager(QSharedPointer<SimpleSwitchReplica> ptr)
{

}

void DatabaseManager::generateTables()
{
    QSqlQuery query(db);

    //TeamMembers table
    bool rc = query.exec("create table TeamMembers"
                         "(memberID integer primary key, "
                         "name varchar(20), "
                         "age integer, "
                         "position varchar(20))");

    if(rc != 1) {
        qDebug() << "teamMembers Error" ;
    } else {
        qDebug() << "TeamMember Table created successfully";
    }

    //Projects table
    rc = query.exec("create table Projects "
                    "(projectID integer primary key, "
                    "number integer, "
                    "customer varchar(20), "
                    "role varchar(20),"
                    "memberID integer,"
                    "FOREIGN KEY(memberID) REFERENCES TeamMembers(memberID))"
                    );
    if(rc != 1) {
        qDebug() << "projects Error";
    } else {
        qDebug() << "projects Table created successfully";
    }
}

void DatabaseManager::insertPerson(const int index, const Person& member)
{
    QSqlQuery query(db);

    QString formattedStr = QString("insert into TeamMembers (memberID, name, age, position)"\
                                   " values(%1, '%2', %3, '%4');").arg(QString::number(index), member.name(), QString::number(member.age()), member.position());
    qDebug() << "formattedStr of insertPerson: " << formattedStr;
    bool rc =  query.exec(formattedStr);
    if(rc != 1) {
        qDebug() << QString("insert member: %1 failed").arg(member.name());
    } else {
        qDebug() << QString("insert member: %1 successfully").arg(member.name());
    }
}

void DatabaseManager::insertProject(const int index, const Project &project, const int memberId)
{
    QSqlQuery query(db);

    QString formattedStr = QString("insert into Projects (projectID, number, customer, role, memberID)"\
                                   " values(%1, %2, '%3', '%4', %5)").arg(QString::number(index), QString::number(project.number()), project.customer(), project.role(), QString::number(memberId));
    qDebug() << "formattedStr of insertProject: " << formattedStr;
    bool rc =  query.exec(formattedStr);
    if(rc != 1) {
        qDebug() << QString("insert project: %1 failed").arg(project.customer());
    } else {
        qDebug() << QString("insert %1 successfully").arg(project.customer());
    }
}

void DatabaseManager::storeModel()
{

}
