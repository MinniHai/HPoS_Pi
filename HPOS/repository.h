#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <QSqlDatabase>
#include <QObject>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QVariant>
#include <QList>
#include <QHash>
#include <QHashIterator>

class Repository
{

public:
    Repository();
    void setSelectQuery(QString select, QString from);
    void setSelectQuery(QString select, QString from, QString where, QString equal);
    void setSelectQuery(QString select, QString from,
                        QString where1, QString equal1,
                        QString where2, QString equal2,
                        QString where3, QString equal3);

    void setSelectLikeQuery(QString select, QString from, QString where, QString equal);
    void setSelectLikeORQuery(QString select, QString from
                              , QString where1, QString equal1
                              , QString where2, QString equal2
                             );
    void setSelectLikeORQuery(QString select, QString from
                              , QString where1, QString equal1
                              , QString where2, QString equal2
                              , QString where3, QString equal3
                             );

    void setInsertQuery(QString into, QHash<QString, QString> hash);

    Repository *getEntityByQuery();

    QList<Repository *>getListEntityByQuery();
    virtual Repository *getResultSet() = 0;
    QSqlQuery query;
protected:
    QSqlDatabase *database;

};

#endif // REPOSITORY_H
