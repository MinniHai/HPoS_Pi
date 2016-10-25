#include "e_user.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include "utils.h"
#include "e_role.h"


E_User::E_User()
{
}

E_User *E_User::getResultSet()
{
    E_User *user = new E_User();
    user->lastname = (query.value(query.record().indexOf("lastName")).toString());
    user->firstname = (query.value(query.record().indexOf("firstName")).toString());
    user->phone = (query.value(query.record().indexOf("phone")).toString());
    roleType = new E_Role();
    user->roleType = roleType->getRoleByID(query.value(query.record().indexOf("roleID")).toString());
    return user;
}

E_User *E_User::getUserByPincode(QString pinCode)
{
    Repository *user = new E_User();
    user->setSelectQuery("*", "User", "pinCode", pinCode);
    return (E_User *) user->getEntityByQuery();
}

QList<E_User *> E_User::getAllUser()
{
    QList <E_User *> listUser;

    Repository *userRepo = new E_User();
    userRepo->setSelectQuery("*", "User");
    foreach(Repository *item, userRepo->getListEntityByQuery())
    {
        listUser.append((E_User *)item);
    }
    return listUser;

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

QList<E_User *> E_User::SearchByUserName(QString name)
{
    QList <E_User *> listUser;

    Repository *userRepo = new E_User();
    userRepo->setSelectLikeORQuery("*", "User", "lastName", name, "firstName", name);
    foreach(Repository *item, userRepo->getListEntityByQuery())
    {
        listUser.append((E_User *)item);
    }
    return listUser;

}

bool E_User::insertUser(QHash<QString, QString> user)
{
    Repository *userRepo = new E_User();
    userRepo->setInsertQuery("User", user);
    return userRepo->query.exec();
}
