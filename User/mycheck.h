#ifndef MYCHECK_H
#define MYCHECK_H

#include <QObject>
#include <QRegularExpression>
#include <QRegularExpressionMatch>
#include <QDebug>

class MyCheck : public QObject
{
    Q_OBJECT
public:
    explicit MyCheck(QObject *parent = nullptr);

    Q_INVOKABLE bool checkName(const QString& inputName);
    Q_INVOKABLE bool checkAge(const QString& inputAge);
    Q_INVOKABLE bool checkPosition(const QString& inputPos);

private:
    QString pattern;
    QRegularExpression re;
    QRegularExpressionMatch match;

};

#endif // MYCHECK_H
