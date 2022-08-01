#include "mycheck.h"

MyCheck::MyCheck(QObject *parent)
    : QObject{parent}
{

}

bool MyCheck::checkName(const QString &inputName)
{
    re.setPattern("[^(a-zA-Z)]+");
    match = re.match(inputName);
    if(match.hasMatch() && (!inputName.isEmpty())) {
        qDebug() << inputName << " not allowed";
    } else{
        qDebug() << inputName << "ok";
    }

}

bool MyCheck::checkAge(const QString &inputAge)
{
    re.setPattern("[^(1-9)]+");
    match = re.match(inputAge);
    if(match.hasMatch() && (!inputAge.isEmpty())) {
        qDebug() << inputAge << " not allowed";
    } else{
        qDebug() << inputAge << "ok";
    }
}

bool MyCheck::checkPosition(const QString &inputPos)
{
    re.setPattern("[^(a-zA-Z)]+");
    match = re.match(inputPos);
    if(match.hasMatch() && (!inputPos.isEmpty())) {
        qDebug() << inputPos << " not allowed";
    } else{
        qDebug() << inputPos << "ok";
    }
}
