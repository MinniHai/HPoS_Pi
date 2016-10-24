#ifndef E_BARCODE_H
#define E_BARCODE_H
#include <QString>
#include "repository.h"

class E_Product;
class E_Manufacturer;
class E_Country;

class E_Barcode : public Repository
{
public:

    E_Barcode();
    E_Barcode *getResultSet();
    static E_Barcode *getBarcode(QString countryPrefix, QString manufacturerPrefix, QString productPrefix);
    static E_Barcode *getBarcodeByProID(QString proID);

    QString countryPrefix;
    QString manufacturerPrefix;
    QString productPrefix;
    int checkDigit;
    QString imDate;
    QString imTime;

    E_Product *product; //get by ID
    E_Manufacturer *manufacturer;//get by prefix
    E_Country *country;//get by prefix

};

#endif // E_BARCODE_H
