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

    static Server &instance();// Singleton

    //prohibit copying object
    Server(const Server &) = delete;
    Server & operator = (const Server &) = delete;

    //slots for exchanging data
    virtual void source_to_rep();// Send members project1 to rep1
    virtual void source_to_rep2();// Send members project1 to rep2

signals:
    void notifyQml(QString parameter);//notify Sever UI when stop download + parse json data (For UI)
    void notifyPersonSender(const int mOrdinal);//async networking

private slots:
    void dataReadyRead();//Store Data => mDataBuffer
    void dataReadFinished();//Parse Json
    void startSend(const int mOrdinal);//This function will be invoked as soon as finish get data from network

private:
    //explicit Sever(SimpleSwitchSimpleSource *parent = nullptr);
    Server();

    QNetworkAccessManager *mNetManager;
    QNetworkReply *mNetReply;
    QByteArray *mDataBuffer;
    QVector<Person> mMembers;//project1 members
    QVector<Person> mMembers2;//project2 members
    int mOrdinal;
};



#endif // SERVER_H
