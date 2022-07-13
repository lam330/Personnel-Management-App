#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QSharedPointer>
#include <QVector>
#include <QTimer>
#include <QAbstractListModel>
#include <QString>

#include "rep_SimpleSwitch_replica.h"

class Client : public QAbstractListModel
{
    Q_OBJECT
    enum PersonRoles{
        NameRole = Qt::UserRole + 1,
        AgeRole,
        PositionRole,
        ExperienceRole
    };
public:
    Client(QSharedPointer<SimpleSwitchReplica> ptr);

    Client();
    ~Client() {
        qDebug() << "Client die";
    }
    void initConnections();// Function to connect signals and slots of source and client

    //interface methods
    //Read from QML
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    //Set from QML
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex& index) const;

    //Help methods


    //store Data
    Q_INVOKABLE void storeModel();
    Q_INVOKABLE void loadDataFromDatabase();
    Q_INVOKABLE void deleteData();


Q_SIGNALS:
    void echoEditedPerson(Person editedPerson);
    void requireHostData();
public Q_SLOTS:
    void recSwitchPerson_slot(); // slot to receive source person
    void getDataFromSource();
    void timeout_slot();
     QVector<Person> getMembers();
private:
    Person clientSwichPerson;
    QSharedPointer<SimpleSwitchReplica> reptr;// holds reference to replica
    QTimer *stateChangeTimer;

    QVector<Person> mMembers;


};

#endif // CLIENT_H
