#include "client2.h"


Client2::Client2(QSharedPointer<SimpleSwitchReplica> ptr) :
    reptr(ptr)
{
    qDebug() << "Replica Node2 Started";
    initConnections();
}

void Client2::initConnections()
{
    QObject::connect(this, &Client2::requireHostData, reptr.data(), &SimpleSwitchReplica::source_to_rep2);
    // connect source replica signal currStateChanged() with client's recSwitchState() slot to receive source's current state
    QObject::connect(reptr.data(), &SimpleSwitchReplica::personChanged, this, &Client2::recSwitchPerson_slot2);

    //check state
    QObject::connect(reptr.data(), &QRemoteObjectReplica::stateChanged, [&](QRemoteObjectReplica::State state, QRemoteObjectReplica::State oldState){
        qDebug() << "Old state: " << oldState;
        qDebug() << "Current state: " << state;
    });

    if(reptr->isReplicaValid()) {
        qDebug() << "replica2 has been initialized and has a valid connection";
    } else {
        qDebug() << "Replica2 connection failed";
    }
}

void Client2::recSwitchPerson_slot2()
{

}
