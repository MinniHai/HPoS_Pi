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
    void analysisBarcode(QString barcode);
    static E_Barcode *getBarcode(QString barcode);
    static E_Barcode *getBarcodeByProID(QString proID);
    static QList<E_Barcode *> searchBarcode(QString barcode);
    static QList<E_Barcode *> getBarcodeByManuRefix(QString prefix);
    static QList<E_Barcode *> getAllBarcodeSortedByProID(QString proID);
    static bool insertBarcode(QHash<QString, QString> barcode);
    static bool upateBarcode(QHash<QString, QString> hash, QString barcodeID);
    static bool upateBarcode(QHash<QString, QString> hash, QString countryPr, QString productPr, QString manufacturerPr);
    static bool deleteBarcode(QString barcodeID);

    QString countryPrefix;
    QString manufacturerPrefix;
    QString productPrefix;
    QString checkDigit;
    QString imDate;
    QString imTime;
    QString proID;
    QString barcode;
    int barcodeID;
    int quantity;
    ulong cost ;

    E_Product *product; //get by ID
    E_Manufacturer *manufacturer;//get by prefix
    E_Country *country;//get by prefix

};

#endif // E_BARCODE_H
