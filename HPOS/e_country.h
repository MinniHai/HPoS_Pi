#ifndef E_COUNTRY_H
#define E_COUNTRY_H

#include <QString>

class E_Country
{
public:
    QString prefix;
    QString name;
    QString description;
    E_Country();
    static QString getCountryNameByPrefix(QString prefix);
};

#endif // E_COUNTRY_H
