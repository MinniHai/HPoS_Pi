#ifndef USER_H
#define USER_H
#include <QString>
#include "repository.h"
#include <QList>
class Utils;
class E_Role;
class E_State;

class E_User : public Repository
{
public:
    E_User();
    E_User *getResultSet();
    E_User *getUserByPincode(QString pinCode);
    static QList <E_User *> getAllUser();
    QString getFirstName();
    QString getUserName();
    void setUserName(QString username);
    static QList<E_User *> SearchByUserName(QString name, QString stateID);
    static bool insertUser(QHash<QString, QString> user);
    static bool upateUser(QHash<QString, QString> hash, QString userId);
    static bool deleteUser(QString userID);
    static int getMaxID();

    QString userID;
    QString phone;
    QString username;
    QString pwd;
    QString pincode;
    QString lastname;
    QString firstname;
    QString age;
    QString DOB;
    QString idCard;
    QString roleID;
    QString picUrl;

    int stateID;
    QString activeTime;
    QString endTime;

    E_State *state;
    E_Role *roleType;
private:
    Utils *utils;

};

#endif // USER_H
