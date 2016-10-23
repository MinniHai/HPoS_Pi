#include "e_user.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include "utils.h"


E_User::E_User()
{
}

E_User *E_User::getResultSet()
{
    E_User *user = new E_User();
    user->setUserName(query.value(query.record().indexOf("username")).toString());
    qDebug() << user->username;
    return user;
}

E_User *E_User::getUserByPincode(QString pinCode)
{
    Repository *user = new E_User();
    user->setSelectQuery("*", "User", "pinCode", pinCode);
    return (E_User *) user->getEntityByQuery();
}

QString E_User::getFirstName()
{
    return firstname;
}
QString E_User::getUserName()
{
    return username;
}
void E_User::setUserName(QString username)
{
    this->username = username;
}
