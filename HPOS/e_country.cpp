#include "e_country.h"
#include "utils.h"

E_Country::E_Country()
{

}

E_Country *E_Country::getResultSet()
{
    E_Country *country = new E_Country();
    country->prefix = query.value(query.record().indexOf("countryPrefix")).toString();
    country->name = query.value(query.record().indexOf("countryName")).toString();
    country->description = query.value(query.record().indexOf("description")).toString();
    return country;
}

E_Country *E_Country::getCountryByPrefix(QString prefix)
{
    Repository *countryRepo = new E_Country();
    countryRepo->setSelectQuery("*", "Country", "countryPrefix", prefix);
    return (E_Country *)countryRepo->getEntityByQuery();
}
