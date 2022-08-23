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
    QString path = "E:/Qt_again/MyProject/Github/Database/database.db";
    db = QSqlDatabase::addDatabase("QSQLITE");
    qDebug() << "The connection name: " << QSqlDatabase::connectionNames();
    db.setDatabaseName(path);
    bool test = db.open();

    if(test) {
        qDebug() << "Opened data file";
    }
    //generateTables();
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

void DatabaseManager::updatePerson(const int index, const Person &member)
{
    QSqlQuery query(db);

    QString formattedStr = QString("update TeamMembers set name = '%1', age = %2, position = '%3' where memberID = %4")
                                   .arg(member.name(), QString::number(member.age()), member.position(), QString::number(index));
    qDebug() << "formattedStr of updatePerson: " << formattedStr;
    bool rc =  query.exec(formattedStr);
    if(rc != 1) {
        qDebug() << QString("update member: %1 failed").arg(member.name());
    } else {
        qDebug() << QString("update %1 successfully").arg(member.name());
    }
}

void DatabaseManager::updateProject(const int index, const Project &project)
{
    QSqlQuery query(db);

    QString formattedStr = QString("update Projects set number = %1, customer = '%2', role = '%3' where memberID = %4 and number = %1")
                                   .arg(QString::number(project.number()), project.customer(), project.role(), QString::number(index));
    qDebug() << "formattedStr of updatteProject: " << formattedStr;
    bool rc =  query.exec(formattedStr);
    if(rc != 1) {
        qDebug() << QString("update project: %1 failed").arg(project.customer());
    } else {
        qDebug() << QString("update %1 successfully").arg(project.customer());
    }
}

void DatabaseManager::deleteData()
{
    QSqlQuery query(db);
    //delete TeamMembers
    QString formattedStr = QString("delete from TeamMembers");
    bool rc =  query.exec(formattedStr);
    if(rc != 1) {
        qDebug() << QString("delete table TeamMembers failed");
    } else {
        qDebug() << QString("delete table TeamMembers successfully");
    }
    //delete
    formattedStr = QString("delete from Projects");
    rc =  query.exec(formattedStr);
    if(rc != 1) {
        qDebug() << QString("delete table Projects failed");
    } else {
        qDebug() << QString("delete table Projects successfully");
    }
}

QVector<Person> DatabaseManager::   selectData()
{
    QSqlQuery queryProject(db);
    QSqlQuery queryPerson(db);
    QVector<Project>projects;
    QVector<Person> members;

    //Get projects
    QString str = QString("select number, customer, role, memberID from Projects");
    bool rc =  queryProject.exec(str);
    if(rc != 1) {
        qDebug() << QString("get projects falied");
    } else {
        qDebug() << QString("get projects successfully");
    }

    //Get members
    str = QString("select name, age, position from TeamMembers");
    rc =  queryPerson.exec(str);
    if(rc != 1) {
        qDebug() << QString("get members falied");
    } else {
        qDebug() << QString("get members successfully");
    }

    while(queryPerson.next()) {
        QVector<Project> emptyProjects;
        Person tempPerson(queryPerson.value(0).toString(), queryPerson.value(1).toInt(), queryPerson.value(2).toString(), emptyProjects);
        members.append(tempPerson);
    }

    int memberID = 0;
    //Map projects to each member
    while(queryProject.next()) {
        Project tempProject(queryProject.value(0).toInt(), queryProject.value(1).toString(), queryProject.value(2).toString());
        if(memberID != queryProject.value(3).toInt()) { //avoid DungND = 6, Hieu DT = 9
            projects.clear();
        }
        memberID = queryProject.value(3).toInt();
        projects.append(tempProject);
        members[memberID].setProjects(projects);
        qDebug() << members[memberID].name() + " = " << members[memberID].projects().size();
    }

    qDebug() << "data load from database";
    for(int i = 0; i < members.size(); i++) {
        qDebug() << members.at(i).name();
        qDebug() << "Size: " << members.at(i).projects().size();

        for(int j = 0; j < members.at(i).projects().size(); j++) {
            qDebug() << members.at(i).projects().at(j).customer();

        }
    }

    return members;

}
