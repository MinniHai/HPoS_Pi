#include "e_barcode.h"
#include "utils.h"
#include "e_picture.h"
#include <QSqlError>
#include <QSqlRecord>
#include "e_product.h"
#include "e_country.h"
#include "e_manufacturer.h"

E_Barcode::E_Barcode()
{

}

E_Barcode *E_Barcode::getResultSet()
{
    E_Barcode *barcode = new E_Barcode();
    barcode->countryPrefix = query.value(query.record().indexOf("countryPrefix")).toString();;
    barcode->manufacturerPrefix = query.value(query.record().indexOf("manuPrefix")).toString();;
    barcode->productPrefix = query.value(query.record().indexOf("productPrefix")).toString();;
    barcode->imDate = query.value(query.record().indexOf("imDate")).toString();
    barcode->imTime = query.value(query.record().indexOf("imTime")).toString();
    return barcode;
}

E_Barcode *E_Barcode::getBarcodeByProID(QString proID)
{
    Repository *barcodeRepository = new E_Barcode();
    barcodeRepository->setSelectQuery("*", "Barcode",
                                      "proID", proID
                                     );
    return (E_Barcode *) barcodeRepository->getEntityByQuery();
}

E_Barcode *E_Barcode::getBarcode(QString countryPrefix, QString manufacturerPrefix, QString productPrefix)
{
    Repository *barcodeRepository = new E_Barcode();
    barcodeRepository->setSelectQuery("*", "Barcode",
                                      "countryPrefix", countryPrefix,
                                      "manuPrefix", manufacturerPrefix,
                                      "productPrefix", productPrefix
                                     );
    return (E_Barcode *) barcodeRepository->getEntityByQuery();
}
