#include "e_user.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include <QSqlRecord>
#include "utils.h"
#include "e_role.h"
#include "e_state.h"

E_User::E_User()
{
    activeTime = "";
    endTime = "";
}

E_User *E_User::getResultSet()
{
    E_User *user = new E_User();

    user->userID = (query.value(query.record().indexOf("userID")).toString());
    user->lastname = (query.value(query.record().indexOf("lastName")).toString());
    user->firstname = (query.value(query.record().indexOf("firstName")).toString());
    user->idCard = (query.value(query.record().indexOf("idCard")).toString());
    user->pincode = (query.value(query.record().indexOf("pinCode")).toString());
    user->phone = (query.value(query.record().indexOf("phone")).toString());
    user->DOB = (query.value(query.record().indexOf("DOB")).toString());
    user->stateID = query.value(query.record().indexOf("stateID")).toInt();
    user->activeTime = query.value(query.record().indexOf("activeTime")).toString();
    user->endTime = query.value(query.record().indexOf("endTime")).toString();
    user->picUrl = query.value(query.record().indexOf("pictureUrl")).toString();
    user->pwd = query.value(query.record().indexOf("pwd")).toString();
    user->roleID = query.value(query.record().indexOf("roleID")).toInt();

    user->state = E_State::getStateByID(QString::number(user->stateID));
    user->roleType = E_Role::getRoleByID(query.value(query.record().indexOf("roleID")).toString());
    return user;
}

int E_User::getMaxID()
{
    Repository *repository = new E_User();
    repository->setSelectQuery("MAX(userID)", "User");
    if(repository->query.exec())
    {
        if(repository->query.next())
        {
            return repository->query.value(repository->query.record().indexOf("MAX(userID)")).toInt();
        }
    }
    return -1;
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
    userRepo->setSelectQuery("*", "User","stateID","1");
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

QList<E_User *> E_User::SearchByUserName(QString name, QString stateID)
{
    QList <E_User *> listUser;

    Repository *userRepo = new E_User();
    userRepo->setSelectLikeANDQuery("*", "User", "lastName", name, "firstName", name, "stateID", stateID);
    foreach(Repository *item, userRepo->getListEntityByQuery())
    {
        listUser.append((E_User *)item);
    };
    return listUser;

}

bool E_User::insertUser(QHash<QString, QString> user)
{
    Repository *userRepo = new E_User();
    userRepo->setInsertQuery("User", user);
    return userRepo->query.exec();
}

bool E_User::upateUser(QHash<QString, QString> hash, QString userId)
{
    Repository *userRepo = new E_User();
    userRepo->setUpdateQuery("User", hash, "userID", userId);
    return userRepo->query.exec();
}

bool E_User::deleteUser(QString userID)
{
    Repository *userRepo = new E_User();
    userRepo->setDeleteQuery("User", "userID", userID);
    return userRepo->query.exec();
}
