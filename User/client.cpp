#include "client.h"
#include "databasemanager.h"
#include <QRegExp>
#include <QStringList>

Client::Client()
{

}

// constructor
Client::Client(QSharedPointer<SimpleSwitchReplica> ptr) :
    reptr(ptr)
{
    qDebug() << "Client::Client(QSharedPointer<SimpleSwitchReplica> ptr)";
    stateChangeTimer = new QTimer(this); // Initialize timer
    QObject::connect(stateChangeTimer, &QTimer::timeout, this, &Client::timeout_slot); // connect timeout() signal from stateChangeTimer to timeout_slot() of simpleSwitch
    stateChangeTimer->start(2000); // Start timer and set timout to 2 seconds
    qDebug() << "Replica Node Started";
    initConnections();

}

void Client::initConnections()
{
    // initialize connections between signals and slots
    //connect to get data => Sever begin fetching
    QObject::connect(this, &Client::requireHostData, reptr.data(), &SimpleSwitchReplica::source_to_rep);

    // connect source replica signal currStateChanged() with client's recSwitchState() slot to receive source's current state
    QObject::connect(reptr.data(), &SimpleSwitchReplica::personChanged, this, &Client::recSwitchPerson_slot);
    QObject::connect(reptr.data(), &SimpleSwitchReplica::ordinalChanged, this, &Client::recOrdinal_slot);

    // connect client's echoSwitchState(..) signal with replica's server_slot(..) to echo back received state
    //    QObject::connect(this, &Client::echoEditedPerson, reptr.data(), &SimpleSwitchReplica::rep_to_source);

    //check state
    QObject::connect(reptr.data(), &QRemoteObjectReplica::stateChanged, [&](QRemoteObjectReplica::State state, QRemoteObjectReplica::State oldState){
        qDebug() << "Old state: " << oldState;
        qDebug() << "Current state: " << state;
    });

    if(reptr->isReplicaValid()) {
        qDebug() << "replica has been initialized and has a valid connection";
    } else {
        qDebug() << "Replica connection failed";
    }


}

//QAbstractListModel
int Client::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    //    qDebug() << "rowCount => mMembers.size() = " << mMembers.size();
    return mMembers.size();
}

QVariant Client::data(const QModelIndex &index, int role) const
{
    //     qDebug() << "data()";
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

bool Client::setData(const QModelIndex &index, const QVariant &value, int role)
{
    //    qDebug() << "setData(const QModelIndex &index, const QVariant &value, int role)";

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

Qt::ItemFlags Client::flags(const QModelIndex &index) const
{
    if(!index.isValid()) {
        return Qt::NoItemFlags;
    }
    return Qt::ItemIsEditable;
}

void Client::storeModel()
{
    int count = 0;
    for(int i = 0;i < mMembers.size(); i++) {
        Person tempMember = mMembers.at(i);
        DatabaseManager::instance().insertPerson(i, tempMember);
        for(int j = 0; j < tempMember.projects().size(); j++) {
            count++;
            Project tempProject = tempMember.projects().at(j);
            DatabaseManager::instance().insertProject(count, tempProject, i);
        }
    }
}

void Client::loadDataFromDatabase()
{
    qDebug() << "loadDataFromDatabase()";
    beginResetModel();
    mMembers = DatabaseManager::instance().selectData();
    endResetModel();
}

void Client::deleteData()
{
    beginResetModel();
    mMembers.clear();
    endResetModel();
}

void Client::updatePerson(const int &index, const QString &newName, const QString &newAge, const QString &newPos, QString newProjects)
{
    beginResetModel();
    mMembers[index].setName(newName);
    mMembers[index].setAge(newAge.toInt());
    mMembers[index].setPosition(newPos);

    updateProject(index, newProjects);

    endResetModel();
    //    mMembers[index].setProjects(newPos);
    //  Update sql
    DatabaseManager::instance().updatePerson(index, mMembers[index]);
}

void Client::updateProject(const int &index, QString newProjects)
{
    //seperate input text => use regex => project1 \n project2 \n....\n projectn
    QStringList splitedText = newProjects.split("\n");
    for ( const auto& project : splitedText  )
    {
        qDebug() << project;//format of a project = no. customer role
        QRegExp rx("([0-9]*).\\s([a-zA-Z]{1,10})\\s([a-zA-Z]{1,10})");
        int pos = rx.indexIn(project);
        QStringList elements = rx.capturedTexts();

        QStringList::iterator it = elements.begin();
        int i = 0;

        Project tempProject;
        QVector<Project> tempListProject;

        while (it != elements.end()) {
            qDebug() << i << "=" <<(*it);

            switch (i) {
            case 0:{
                //do nothing
                break;
            }
            case 1:{
                tempProject.setNumber((*it).toInt());
                break;
            }
            case 2:{
                tempProject.setCustomer((*it));
                break;
            }
            case 3:{
                tempProject.setRole((*it));
                break;
            }
            default:
                break;
            }
            tempListProject.append(tempProject);


            i++;
            ++it;
        }
        beginResetModel();
        mMembers[index].setProjects(tempListProject);
        endResetModel();
        DatabaseManager::instance().updateProject(index, tempProject);

    }

    //    //Reset model
    //    beginResetModel();
    ////    mMembers[index].setName(newName);
    ////    mMembers[index].setAge(newAge.toInt());
    ////    mMembers[index].setPosition(newPos);
    //    endResetModel();
}

QHash<int, QByteArray> Client::roleNames() const
{
    //    qDebug() << "roleNames()";
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[AgeRole] = "age";
    roles[PositionRole] = "position";
    roles[ExperienceRole] = "experience";
    return roles;
}



void Client::recSwitchPerson_slot()
{

    qDebug() << "Received source state "<<reptr.data()->person().name() << "  " << reptr.data()->person().age();
    for(int i = 0; i < reptr.data()->person().projects().size(); i++) {
        qDebug() << reptr.data()->person().projects().at(i).customer();
    }

    const int index = mMembers.size();

    if(recOrdinal_slot() == 1) {
        beginInsertRows(QModelIndex(),index,index);//Insert new person
        mMembers.push_back(reptr.data()->person());
        endInsertRows();
    }
    qDebug() << "mMember.size() " << mMembers.size();

}

int Client::recOrdinal_slot()
{
    return reptr.data()->ordinal();
}

void Client::getDataFromSource()
{
    //    qDebug() << "getDataFromSource()";
    emit requireHostData();

}

void Client::timeout_slot()// check connection
{


}

QVector<Person> Client::getMembers()
{
    return mMembers;
}
