#include "repository.h"
#include "utils.h"

Repository::Repository()
{
    database = Utils::instance()->getDB();
}

void Repository::setInsertQuery(QString into, QHashIterator<QString, QString> values)
{
    if(database)
    {
        if(database->open())
        {
            query = QSqlQuery(*database);

            QString queryString = "INSERT " + into + " (";
            QString valuesString = "";
            QString column = "(";
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
            query.prepare("SELECT " + select + " FROM " + from + " WHERE "
                          + where1 + "=" + " :equal1" + " AND "
                          + where2 + "=" + " :equal2" + " AND "
                          + where3 + "=" + " :equal3"
                         );
            query.bindValue(":equal1", equal1);
            query.bindValue(":equal2", equal2);
            query.bindValue(":equal3", equal3);
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
