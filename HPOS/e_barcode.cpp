#include "e_barcode.h"
#include "utils.h"
#include "e_picture.h"
#include <QSqlError>
#include <QSqlRecord>
#include "e_product.h"

E_Barcode::E_Barcode()
{

}

E_Barcode *E_Barcode::getResultSet()
{
    E_Barcode *barcode = new E_Barcode();
    barcode->countryPrefix = countryPrefix;
    barcode->manufacturerPrefix = manufacturerPrefix;
    barcode->productPrefix = productPrefix;
    barcode->product = E_Product::getProductByID(query.value(query.record().indexOf("proID")).toString());
    barcode->product->listPicture = E_Picture::getPictureByProductID(query.value(query.record().indexOf("proID")).toString());
    barcode->imDate = query.value(query.record().indexOf("imDate")).toString();
    barcode->imTime = query.value(query.record().indexOf("imTime")).toString();
    return barcode;
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
