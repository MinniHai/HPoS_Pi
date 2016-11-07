#ifndef E_COUNTRY_H
#define E_COUNTRY_H

#include <QString>
#include "repository.h"

class E_Country: public Repository
{
public:
    QString prefix;
    QString name;
    QString description;

    E_Country();
    static E_Country *getCountryByPrefix(QString prefix);
    E_Country *getResultSet();
};

#endif // E_COUNTRY_H
