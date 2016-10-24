#include "e_manufacturer.h"

E_Manufacturer::E_Manufacturer()
{

}

E_Manufacturer *E_Manufacturer::getResultSet()
{
    //TODO: implement this method
}

E_Manufacturer *E_Manufacturer::getManufacturerByPrefix(QString prefix)
{
    Repository *manuRepo = new E_Manufacturer();
    manuRepo->setSelectQuery("*", "Manufacturer", "manuPrefix", prefix);
    return (E_Manufacturer *)manuRepo->getEntityByQuery();
}
