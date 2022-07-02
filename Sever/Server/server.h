#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QQmlApplicationEngine>
#include <QVector>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QTimer>

#include "rep_SimpleSwitch_source.h"


class Server  : public SimpleSwitchSimpleSource
{
    Q_OBJECT
public:

    ~Server() {
        qDebug() << "Sever die";
    }

    Q_INVOKABLE void fetchData(const QUrl path);
    QVector<Person> getMembers() const;

    static Server &instance();// singleton

    //prohibit copying object
    Server(const Server &) = delete;
    Server & operator = (const Server &) = delete;


    //slots for exchanging data
    virtual void rep_to_source(Person clientPerson);
    virtual void source_to_rep();

public Q_SLOTS:
    void timeout_slot();



signals:
    void notifyQml(QString parameter);//notify Sever UI when stop download + parse json data
    void notifyPersonSender(const QVector<Person> listOfMembers);//async networking

private slots:
    void dataReadyRead();
    void dataReadFinished();//Parse Json
    void startSend(const QVector<Person> listOfMembers);

private:
    //explicit Sever(SimpleSwitchSimpleSource *parent = nullptr);
    Server();

    QNetworkAccessManager *mNetManager;
    QNetworkReply *mNetReply;
    QByteArray *mDataBuffer;
    QVector<Person> mMembers;
    QTimer *checkTimer;


};



#endif // SERVER_H
