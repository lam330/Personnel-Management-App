#include "server.h"

//Sever::Sever(SimpleSwitchSimpleSource *parent)
//    : QObject{parent},
//      mNetManager(new QNetworkAccessManager(this)),
//      mNetReply(nullptr),
//      mDataBuffer(new QByteArray)
//{

//}

Server::Server()
    : mNetManager(new QNetworkAccessManager(this)),
      mNetReply(nullptr),
      mDataBuffer(new QByteArray)
{
    QObject::connect(this, &Server::notifyPersonSender, this, &Server::startSend);//async => why??

    //start timer
    checkTimer = new QTimer(this); // Initialize timer
    QObject::connect(checkTimer, &QTimer::timeout, this, &Server::timeout_slot); // connect timeout() signal from stateChangeTimer to timeout_slot() of simpleSwitch
    checkTimer->start(2000); // Start timer and set timout to 2 seconds
    qDebug() << "Source Node Started";

}


void Server::fetchData(const QUrl path)
{
    qDebug() << "fetchData()";
    //Initialize our API data
    const QUrl API_ENDPOINT(path);//path = http://localhost:8080/
    QNetworkRequest request;
    request.setUrl(API_ENDPOINT);

    mNetReply = mNetManager->get(request);
    connect(mNetReply,&QIODevice::readyRead,this,&Server::dataReadyRead);
    connect(mNetReply,&QNetworkReply::finished,this,&Server::dataReadFinished);
}

QVector<Person> Server::getMembers() const
{
    return mMembers;
}

Server &Server::instance()
{
    static Server server;
    return server;
}


void Server::source_to_rep()
{
    ordinal = 1;
    Server::instance().fetchData(QUrl("http://localhost:8080/")); //acsync

}

void Server::source_to_rep2()
{
    qDebug() << "source_to_rep2()";
    ordinal = 2;
    Server::instance().fetchData(QUrl("http://localhost:8080/")); //acsync
}

void Server::timeout_slot()
{
//    qDebug() << person()
}

void Server::dataReadyRead()
{
    qDebug() << "dataReadyRead()";
    mDataBuffer->append(mNetReply->readAll());
}

void Server::dataReadFinished()
{
    qDebug() << "dataReadFinished()";

    QVector<Project> projectList;//list of projects of one member

    //Parse the JSON
    if( mNetReply->error()){
        qDebug() << "There was some error : " << mNetReply->errorString();
    }else{
        //
        //Turn the data into a json document
        QJsonDocument jsonDoc = QJsonDocument::fromJson(*mDataBuffer);

        //Grab the value array
        QJsonObject data = jsonDoc.object();

        //query by key => get all projects in project list
        QJsonArray projectArray = data["ListProjects"].toArray();
        for(int i = 0; i < projectArray.size(); i++) {
            QJsonObject project = projectArray.at(i).toObject();//object
            QJsonArray memberArray1 = project["Project1"].toArray();
            QJsonArray memberArray2 = project["Project2"].toArray();

            //Get members of project1
            for ( int i = 0; i < memberArray1.size() ; i++){
                QJsonObject member = memberArray1.at(i).toObject();//object
                QJsonArray projectArray = member["Experiences"].toArray();//type JsonArray

                //get projects (experiences) of each member
                for (int j = 0; j < projectArray.size(); j++){
                    QJsonObject   tempProject = projectArray.at(j).toObject();
                    Project project(tempProject["No"].toString().toInt(), tempProject["Customer"].toString(), tempProject["Role"].toString());
                    projectList.append(project);
                }
                Person person(member["Name"].toString(), member["Age"].toString().toInt(), member["Position"].toString(), projectList);
                mMembers.append(person);
                projectList.clear();
            }

            //Get members of project2
            for ( int i = 0; i < memberArray2.size() ; i++){
                QJsonObject member = memberArray2.at(i).toObject();//object
                QJsonArray projectArray = member["Experiences"].toArray();//type JsonArray

                //get projects (experiences) of each member
                for (int j = 0; j < projectArray.size(); j++){
                    QJsonObject   tempProject = projectArray.at(j).toObject();
                    Project project(tempProject["No"].toString().toInt(), tempProject["Customer"].toString(), tempProject["Role"].toString());
                    projectList.append(project);
                }
                Person person(member["Name"].toString(), member["Age"].toString().toInt(), member["Position"].toString(), projectList);
                mMembers2.append(person);
                projectList.clear();
            }

        }

        //check final output of fectch
        qDebug() << "mMembers.size(): " << mMembers.size();
        for( int i = 0; i < mMembers.size(); i++) {
            qDebug() << "mMembers: " << mMembers.at(i).name();
            for(int j =0 ;j < mMembers.at(i).projects().size(); j++) {
                qDebug() << "projects: " << mMembers.at(i).projects().at(j).customer();
            }
        }

        qDebug() << "\n\nmMembers2.size(): " << mMembers2.size();
        for( int i = 0; i < mMembers2.size(); i++) {
            qDebug() << "mMembers2: " << mMembers2.at(i).name();
            for(int j =0 ;j < mMembers2.at(i).projects().size(); j++) {
                qDebug() << "projects: " << mMembers2.at(i).projects().at(j).customer();
            }
        }

//        if(memberArray.size() !=0){
//             //resetModel();
//        }

        //Clear the buffer
        mDataBuffer->clear();
    }

    //notify qml done
    emit notifyQml("Done roi nha");
    emit notifyPersonSender(ordinal);
}

void Server::startSend(const int ordinal)
{
    qDebug() << "startSend()";
    if(ordinal == 1) {
        for(int i = 0; i < mMembers.size(); i++) {
                qDebug() << "i = " << i;
                setPerson(mMembers.at(i));
            }
        mMembers.clear();
    } else {
        for(int i = 0; i < mMembers2.size(); i++) {
                qDebug() << "i2 = " << i;
                setPerson(mMembers2.at(i));
            }
        mMembers.clear();
        mMembers2.clear();

    }

}

//Server* Server::mInstancePtr = nullptr;// static attribute hafta be defined outside of class
