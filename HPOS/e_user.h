#ifndef USER_H
#define USER_H
#include <QString>
#include "repository.h"
class Utils;

class E_User : public Repository
{
public:
    E_User();
    E_User *getResultSet();
    E_User *getUserByPincode(QString pinCode);

    QString getFirstName();
    QString getUserName();
    void setUserName(QString username);
    //TODO: get;set;
private:
    Utils *utils;
    int userID;
    QString username;
    QString pwd;
    int pincode;
    QString lastname;
    QString firstname;
    QString age;
    QString DOB;
    QString idCard;
    QString phone;
    QString roleID;
};

#endif // USER_H
