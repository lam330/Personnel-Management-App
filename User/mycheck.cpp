#include "mycheck.h"

MyCheck::MyCheck(QObject *parent)
    : QObject{parent}
{

}

bool MyCheck::checkName(const QString &inputName)
{
    mRe.setPattern("[^(a-zA-Z)]+");
    mMatch = mRe.match(inputName);
    if(mMatch.hasMatch() && (!inputName.isEmpty())) {
        qDebug() << inputName << " not allowed";
    } else{
        qDebug() << inputName << "ok";
    }

}

bool MyCheck::checkAge(const QString &inputAge)
{
    mRe.setPattern("[^(1-9)]+");
    mMatch = mRe.match(inputAge);
    if(mMatch.hasMatch() && (!inputAge.isEmpty())) {
        qDebug() << inputAge << " not allowed";
    } else{
        qDebug() << inputAge << "ok";
    }
}

bool MyCheck::checkPosition(const QString &inputPos)
{
    mRe.setPattern("[^(a-zA-Z)]+");
    mMatch = mRe.match(inputPos);
    if(mMatch.hasMatch() && (!inputPos.isEmpty())) {
        qDebug() << inputPos << " not allowed";
    } else{
        qDebug() << inputPos << "ok";
    }
}
