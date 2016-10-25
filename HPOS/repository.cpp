#include "repository.h"
#include "utils.h"

Repository::Repository()
{
    database = Utils::instance()->getDB();
}

void Repository::setInsertQuery(QString into, QHash<QString, QString> hash)
{
    if(database)
    {
        if(database->open())
        {
            query = QSqlQuery(*database);

            QString queryString = "INSERT INTO " + into ;
            QString valuesString = " VALUES ( ";
            QString column = "(";
            QHashIterator<QString, QString> values(hash);
            while(values.hasNext())
            {
                values.next();
                if(values.hasNext())
                {
                    valuesString.append(":" + values.key() + " , ");
                    column.append(" " + values.key() + " , ");
                }
                else
                {
                    valuesString.append(":" + values.key() + " )");
                    column.append(" " + values.key() + " )");
                }
            }
            queryString.append(column).append(valuesString);
            qDebug() << queryString;
            query.prepare(queryString);
            while(values.hasPrevious())
            {
                values.previous();
                query.bindValue(":" + values.key(), values.value());
            }
        }
    }
    //TODO: database NULL

}

void Repository::setSelectQuery(QString select, QString from)
{
    if(database)
    {
        if(database->open())
        {
            query = QSqlQuery(*database);
            query.prepare("SELECT " + select + " FROM " + from);
        }
    }
    //TODO: database NULL
}

void Repository::setSelectQuery(QString select, QString from, QString where, QString equal)
{
    if(database)
    {
        if(database->open())
        {
            query = QSqlQuery(*database);
            query.prepare("SELECT " + select + " FROM " + from + " WHERE " + where + "=" + " :equal");
            query.bindValue(":equal", equal);
        }
    }
    //TODO: database NULL
}

void Repository::setSelectQuery(QString select, QString from,
                                QString where1, QString equal1,
                                QString where2, QString equal2,
                                QString where3, QString equal3)
{

    if(database)
    {
        if(database->open())
        {
            query = QSqlQuery(*database);
            QString queryString = "SELECT " + select + " FROM " + from + " WHERE "
                                  + where1 + " = :equal1";
            if(!equal2.isEmpty())
            {
                queryString.append(" AND " + where2 + " = :equal2");
            }
            if(!equal3.isEmpty())
            {
                queryString.append(" AND " + where3 + " = :equal3 ");
            }
            query.prepare(queryString);
            query.bindValue(":equal1", equal1);
            if(!equal2.isEmpty())
            {
                query.bindValue(":equal2",  equal2);
            }
            if(!equal3.isEmpty())
            {
                query.bindValue(":equal3", equal3);
            }
        }
    }
    //TODO: database NULL
}

void Repository::setSelectLikeORQuery(QString select, QString from
                                      , QString where1, QString equal1
                                      , QString where2, QString equal2
                                     )
{
    if(database)
    {
        if(database->open())
        {
            query = QSqlQuery(*database);
            query.prepare("SELECT " + select + " FROM " + from + " WHERE "
                          + where1 + " LIKE :equal1 OR "
                          + where2 + " LIKE :equal2"
                         );
            query.bindValue(":equal1", "%" +  equal1 + "%");
            query.bindValue(":equal2", "%" +  equal2 + "%");
        }
    }
    //TODO: database NULL
}
void Repository::setSelectLikeORQuery(QString select, QString from
                                      , QString where1, QString equal1
                                      , QString where2, QString equal2
                                      , QString where3, QString equal3
                                     )
{
    if(database)
    {
        if(database->open())
        {
            query = QSqlQuery(*database);
            QString queryString = "SELECT " + select + " FROM " + from + " WHERE "
                                  + where1 + " LIKE :equal1";
            if(!equal2.isEmpty())
            {
                queryString.append(" OR " + where2 + " LIKE :equal2");
            }
            if(!equal3.isEmpty())
            {
                queryString.append(" OR " + where3 + " LIKE :equal3 ");
            }

            qDebug() << queryString;
            query.prepare(queryString);
            query.bindValue(":equal1", "%" +  equal1 + "%");
            if(!equal2.isEmpty())
            {
                query.bindValue(":equal2", "%" +  equal2 + "%");
            }
            if(!equal3.isEmpty())
            {
                query.bindValue(":equal3", "%" +  equal3 + "%");
            }
        }
    }
    //TODO: database NULL
}

void Repository::setSelectLikeQuery(QString select, QString from, QString where, QString equal)
{
    if(database)
    {
        if(database->open())
        {
            query = QSqlQuery(*database);
            query.prepare("SELECT " + select + " FROM " + from + " WHERE "
                          + where + " LIKE :equal"
                         );
            query.bindValue(":equal", "%" +  equal + "%");
        }
    }
    //TODO: database NULL
}

Repository *Repository::getEntityByQuery()
{
    if(database->isOpen())
    {
        if(!query.exec())
        {
            if(Utils::instance()->isDebugging())
            {
                qDebug() << "SQL QUERY ERROR:" << query.lastError().text();
            }
        }
        else
        {
            database->close();
            if(query.next())
            {
                return getResultSet();
            }
        }
    }
    else
    {
        if(Utils::instance()->isDebugging())
        {
            qDebug() << "database->lastError().text();";
        }
    }
    return NULL;
}
QList<Repository *> Repository::getListEntityByQuery()
{
    QList<Repository *> listRepository ;
    if(database->isOpen())
    {
        if(!query.exec())
        {
            if(Utils::instance()->isDebugging())
            {
                qDebug() << "SQL QUERY ERROR:" << query.lastError().text();
            }
        }
        else
        {
            database->close();
            while(query.next())
            {
                listRepository.append(getResultSet());
            }
        }
    }
    else
    {
        if(Utils::instance()->isDebugging())
        {
            qDebug() << "database->lastError().text();";
        }
    }
    return listRepository;
}
