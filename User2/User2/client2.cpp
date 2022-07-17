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

void Client2::deleteData()
{
    beginResetModel();
    mMembers.clear();
    endResetModel();
}

int Client2::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    //    qDebug() << "rowCount => mMembers.size() = " << mMembers.size();
    return mMembers.size();
}

QVariant Client2::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= mMembers.count()) {
        return QVariant();
    }
    //The index is valid
    Person person = mMembers[index.row()];

    switch (role) {
    case NameRole:
        return person.name();
    case AgeRole:
        return person.age();
    case PositionRole:
        return person.position();
    case ExperienceRole: {
        QString temp;
        for(int i = 0; i < person.projects().size(); i++) {
            temp += QString::number(person.projects().at(i).number()) + ". ";
            temp += person.projects().at(i).customer() + " ";
            temp += person.projects().at(i).role();
            temp += "\n";
        }
        return temp;
    }
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> Client2::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[AgeRole] = "age";
    roles[PositionRole] = "position";
    roles[ExperienceRole] = "experience";
    return roles;
}

bool Client2::setData(const QModelIndex &index, const QVariant &value, int role)
{
    Person person = mMembers[index.row()];
    bool somethingChanged = false;

    switch (role) {
    case NameRole:
    {
        if( person.name()!= value.toString()){
            qDebug() << "Changing name for " << person.name();
            person.setName(value.toString());
            somethingChanged = true;
        }
    }
        break;
    case AgeRole:
    {
        if( person.age()!= value.toString()){
            qDebug() << "Changing age for " << person.name();
            person.setAge(value.toInt());
            somethingChanged = true;
        }
    }
        break;
    case PositionRole:
    {
        if( person.age()!= value.toInt()){
            qDebug() << "Changing age for " << person.name();
            person.setAge(value.toInt());
            somethingChanged = true;
        }
    }
        break;
    case ExperienceRole:
    {

    }
    }

    if( somethingChanged){
        emit dataChanged(index,index,QVector<int>() << role);
        return true;
    }
    return false;
}

Qt::ItemFlags Client2::flags(const QModelIndex &index) const
{
    if(!index.isValid()) {
        return Qt::NoItemFlags;
    }
    return Qt::ItemIsEditable;
}

void Client2::recSwitchPerson_slot2()
{
    qDebug() << "Received source state "<<reptr.data()->person().name() << "  " << reptr.data()->person().age();
    for(int i = 0; i < reptr.data()->person().projects().size(); i++) {
        qDebug() << reptr.data()->person().projects().at(i).customer();
    }

    const int index = mMembers.size();
    beginInsertRows(QModelIndex(),index,index);//Insert new person
    mMembers.push_back(reptr.data()->person());
    endInsertRows();

    qDebug() << "mMember.size() " << mMembers.size();
}

void Client2::getDataFromSource()
{
    qDebug() << "getDataFromSource()";

    emit requireHostData();
}
