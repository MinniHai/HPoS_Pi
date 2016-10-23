#ifndef UTILS_H
#define UTILS_H
#include<QSqlDatabase>
#include<QtSql>
#include<qsqldatabase.h>
class Utils
{
public:
    static Utils *s_instance;
    static Utils *instance();

    QSqlDatabase *getDB();
    bool isDebugging();
    void showMessageBox();
    Utils();
    QSqlDatabase *database;
protected:
private:
    bool is_Debug;
    QString dbDriver;
    QString dbHostName ;
    QString dbName;
    QString dbUsername ;
    QString dbPwd ;
    int dbPort;

};


#endif // UTILS_H
