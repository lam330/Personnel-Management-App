#ifndef CLIENT2_H
#define CLIENT2_H
#include "rep_SimpleSwitch_replica.h"

#include <QObject>
#include <QSharedPointer>
#include <QString>
#include <QAbstractListModel>
#include <QVector>

class Client2 : public QAbstractListModel
{
    Q_OBJECT
    enum PersonRoles{
        NameRole = Qt::UserRole + 1,
        AgeRole,
        PositionRole,
        ExperienceRole
    };
public:
    Client2(QSharedPointer<SimpleSwitchReplica> ptr);
    ~Client2() {
        qDebug() << "Client2 die";
    }
    void initConnections();// Function to connect signals and slots of source and client

    //interface methods
    Q_INVOKABLE void deleteData();
    //Read from QML
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    //Set from QML
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    Qt::ItemFlags flags(const QModelIndex& index) const;

public Q_SLOTS:
    void recSwitchPerson_slot2(); // slot to receive source person
    void getDataFromSource();



signals:
    void requireHostData();
private:
    QSharedPointer<SimpleSwitchReplica> reptr;// holds reference to replica
    QVector<Person> mMembers;
};

#endif // CLIENT2_H
