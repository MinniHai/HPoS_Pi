#ifndef USER_H
#define USER_H
#include <QString>
#include "repository.h"
#include <QList>
class Utils;
class E_Role;
class E_User : public Repository
{
public:
    E_User();
    E_User *getResultSet();
    E_User *getUserByPincode(QString pinCode);
    static QList <E_User *> getAllUser();
    E_Role *roleType;
    QString phone;
    QString username;
    QString getFirstName();
    QString getUserName();
    void setUserName(QString username);
    static QList<E_User *> SearchByUserName(QString name);
    static bool insertUser(QHash<QString, QString> user);
    //TODO: get;set;
    int userID;

    QString pwd;
    int pincode;
    QString lastname;
    QString firstname;
    QString age;
    QString DOB;
    QString idCard;
    QString roleID;
private:
    Utils *utils;

};

#endif // USER_H
