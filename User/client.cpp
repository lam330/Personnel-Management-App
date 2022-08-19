#include "client.h"
#include "databasemanager.h"
#include <QRegExp>
#include <QStringList>

Client::Client()
{

}

// constructor
Client::Client(QSharedPointer<SimpleSwitchReplica> ptr) :
    mReptr(ptr)
{
    qDebug() << "Client::Client(QSharedPointer<SimpleSwitchReplica> ptr)";
    qDebug() << "Replica Node Started";
    initConnections();

}

void Client::initConnections()
{
    // initialize connections between signals and slots
    //connect to get data => Sever begin fetching
    QObject::connect(this, &Client::requireHostData, mReptr.data(), &SimpleSwitchReplica::source_to_rep);

    // connect source replica signal currStateChanged() with client's recSwitchState() slot to receive source's current state
    QObject::connect(mReptr.data(), &SimpleSwitchReplica::personChanged, this, &Client::recSwitchPerson);
    QObject::connect(mReptr.data(), &SimpleSwitchReplica::ordinalChanged, this, &Client::recOrdinal);

    //check Replica state
    QObject::connect(mReptr.data(), &QRemoteObjectReplica::stateChanged, [&](QRemoteObjectReplica::State state, QRemoteObjectReplica::State oldState){
        qDebug() << "Old state: " << oldState;
        qDebug() << "Current state: " << state;
    });

    if(mReptr->isReplicaValid()) {
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

void Client::clearModel()
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
    DatabaseManager::instance().updatePerson(index, mMembers[index]);
}

void Client::updateProject(const int &index, QString newProjects)
{
    //Split input text => project1 \n project2 \n....\n projectn
    Project tempProject;
    QVector<Project> tempListProject;
    qDebug() << "updateProject";
    QStringList splitedText = newProjects.split("\n");
    for ( const auto& project : splitedText  )
    {
        qDebug() << project;//format of a project = no. customer role
        QRegExp rx("([0-9]*).\\s([a-zA-Z]{1,10})\\s([a-zA-Z]{1,10})");
        int pos = rx.indexIn(project);
        QStringList elements = rx.capturedTexts();
        QString str;
        int i = 0;

        while(i != elements.size()) {
            i++;
            switch (i) {
            case 0:{
                //do nothing
                break;
            }
            case 1:{
                tempProject.setNumber(elements[i].toInt());
                break;
            }
            case 2:{
                tempProject.setCustomer(elements[i]);
                break;
            }
            case 3:{
                tempProject.setRole(elements[i]);
                break;
            }
            default:
                break;
            }
            if( i % 4 == 0) {
                qDebug() << "i = " << i;
                tempListProject.append(tempProject);
                DatabaseManager::instance().updateProject(index, tempProject);
            }
        }
        mMembers[index].setProjects(tempListProject);
    }
}

QHash<int, QByteArray> Client::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[NameRole] = "name";
    roles[AgeRole] = "age";
    roles[PositionRole] = "position";
    roles[ExperienceRole] = "experience";
    return roles;
}



void Client::recSwitchPerson()
{

    qDebug() << "Received source state "<<mReptr.data()->person().name() << "  " << mReptr.data()->person().age();
    for(int i = 0; i < mReptr.data()->person().projects().size(); i++) {
        qDebug() << mReptr.data()->person().projects().at(i).customer();
    }

    const int index = mMembers.size();

    if(recOrdinal() == 1) {//Add data from source to model
        beginInsertRows(QModelIndex(),index,index);//Insert new person
        mMembers.push_back(mReptr.data()->person());
        endInsertRows();
    }
    qDebug() << "mMember.size() " << mMembers.size();
}

int Client::recOrdinal()
{
    return mReptr.data()->ordinal();
}

void Client::getDataFromSource()
{
    emit requireHostData();
}

QVector<Person> Client::getMembers()
{
    return mMembers;
}
