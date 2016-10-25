#include "e_manufacturer.h"
#include<QDebug>
E_Manufacturer::E_Manufacturer()
{

}

E_Manufacturer *E_Manufacturer::getResultSet()
{
    E_Manufacturer *manufacturer = new E_Manufacturer();
    manufacturer->manuPrefix = query.value(query.record().indexOf("manuPrefix")).toString();
    manufacturer->manuName = query.value(query.record().indexOf("manuName")).toString();
    manufacturer->address = query.value(query.record().indexOf("address")).toString();
    manufacturer->phone = query.value(query.record().indexOf("phone")).toString();
    manufacturer->logoUrl = query.value(query.record().indexOf("logoUrl")).toString();
    return manufacturer;
}

E_Manufacturer *E_Manufacturer::getManufacturerByPrefix(QString prefix)
{
    Repository *manuRepo = new E_Manufacturer();
    manuRepo->setSelectQuery("*", "Manufacturer", "manuPrefix", prefix);
    return (E_Manufacturer *)manuRepo->getEntityByQuery();
}
QList<E_Manufacturer *> E_Manufacturer::searchByName(QString name)
{
    QList<E_Manufacturer *> listManufacture;
    Repository *manuRepo = new E_Manufacturer();
    manuRepo->setSelectLikeQuery("*", "Manufacturer", "manuName", name);
    foreach(Repository *item, manuRepo->getListEntityByQuery())
    {
        listManufacture.append((E_Manufacturer *)item);
    }
    qDebug() << listManufacture.size();
    return listManufacture;
}
