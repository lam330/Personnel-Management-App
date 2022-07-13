#ifndef CLIENT2_H
#define CLIENT2_H
#include "rep_SimpleSwitch_replica.h"

#include <QObject>
#include <QSharedPointer>
#include <QString>


class Client2 : public QObject
{
    Q_OBJECT
public:
    Client2(QSharedPointer<SimpleSwitchReplica> ptr);
    ~Client2() {
        qDebug() << "Client2 die";
    }
    void initConnections();// Function to connect signals and slots of source and client

public Q_SLOTS:
    void recSwitchPerson_slot2(); // slot to receive source person


signals:
    void requireHostData();
private:
    QSharedPointer<SimpleSwitchReplica> reptr;// holds reference to replica


};

#endif // CLIENT2_H
