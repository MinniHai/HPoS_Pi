#ifndef E_MANIFACTURER_H
#define E_MANIFACTURER_H

#include <QString>
#include "repository.h"

class E_Manufacturer : public Repository
{
public:
    E_Manufacturer();
    QString manuPrefix;
    QString manuName;
    QString address;
    QString phone;
    QString logoUrl;

    E_Manufacturer *getResultSet();
    static E_Manufacturer *getManufacturerByPrefix(QString prefix);
    static QList<E_Manufacturer *> searchByName(QString name);
    static bool insertManufacturer(QHash<QString, QString> manufactuerer);
};

#endif // E_MANIFACTURER_H
