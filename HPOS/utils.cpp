#include "utils.h"
#include <QDebug>
#include <QSqlError>
#include <QMessageBox>


Utils *Utils::s_instance;

bool Utils::isDebugging()
{
    return is_Debug;
}
Utils *Utils::instance()
{
    if(!s_instance)
    {
        s_instance = new Utils();
    }
    return s_instance;
}

Utils::Utils()
{
    is_Debug = true;
    dbDriver  = "QMYSQL";
    dbHostName = "127.0.0.1";
    dbName = "HPoS";
    dbUsername = "root";
    dbPwd = "123123";
    dbPort = 3306;
    database = new QSqlDatabase(QSqlDatabase::addDatabase(dbDriver));
    database->setDatabaseName(dbName);
    database->setHostName(dbHostName);
    database->setUserName(dbUsername);
    database->setPassword(dbPwd);
}

QSqlDatabase *Utils::getDB()
{
    if(database->isValid())
    {
        if(isDebugging())
        {
            qDebug() << "database valid";
        }
        return database;
    }
    else
    {
        if(isDebugging())
        {
            qDebug() << "database error " + database->lastError().text();
        }
        return NULL;
    }
}



void Utils::showMessageBox()
{
    QMessageBox::StandardButton box;
}
