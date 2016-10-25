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
    barcode->proID = query.value(query.record().indexOf("proID")).toString();;
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

void E_Barcode::analysisBarcode(QString barcode)
{
    if(barcode.length() > 4)
    {
        countryPrefix = barcode.left(3);
        manufacturerPrefix = barcode.right(barcode.length() - 3);
        productPrefix = barcode.right(barcode.length() - 3);
        if(barcode.length() >= 7)
        {
            manufacturerPrefix = barcode.mid(3, 4);
            if(barcode.length() >= 13)
            {
                productPrefix = barcode.mid(7, 5);
                checkDigit = barcode.right(1);
            }
            else
            {
                productPrefix = barcode.mid(7, barcode.length());
            }

        }
        else
        {
            manufacturerPrefix = barcode.mid(3, barcode.length());
        }
    }
    else
    {
        countryPrefix = barcode;
        manufacturerPrefix = barcode;
        productPrefix = barcode;
    }


}

E_Barcode *E_Barcode::getBarcode(QString barcode)
{
    E_Barcode *barcodeRepository = new E_Barcode();
    barcodeRepository->analysisBarcode(barcode);
    barcodeRepository->setSelectQuery("*", "Barcode",
                                      "countryPrefix", barcodeRepository->countryPrefix,
                                      "manuPrefix", barcodeRepository->manufacturerPrefix,
                                      "productPrefix", barcodeRepository->productPrefix
                                     );
    return (E_Barcode *)barcodeRepository->getEntityByQuery();
}

QList<E_Barcode *> E_Barcode::searchBarcode(QString barcode)
{
    QList<E_Barcode *> barcodeList;
    E_Barcode *barcodeRepository = new E_Barcode();
    barcodeRepository->analysisBarcode(barcode);
    barcodeRepository->setSelectLikeORQuery("*", "Barcode",
                                            "countryPrefix", barcodeRepository->countryPrefix,
                                            "manuPrefix", barcodeRepository->manufacturerPrefix,
                                            "productPrefix", barcodeRepository->productPrefix
                                           );
    foreach(Repository *item, barcodeRepository->getListEntityByQuery())
    {
        barcodeList.append((E_Barcode *)item);
    }
    qDebug() << barcodeList.size();
    return barcodeList;
}
QList<E_Barcode *> E_Barcode::getBarcodeByManuRefix(QString prefix)
{
    QList<E_Barcode *> barcodeList;
    Repository *barcodeRepository = new E_Barcode();
    barcodeRepository->setSelectQuery("*", "Barcode",

                                      "manuPrefix", prefix

                                     );
    foreach(Repository *item, barcodeRepository->getListEntityByQuery())
    {
        barcodeList.append((E_Barcode *)item);
    }
    qDebug() << barcodeList.size();
    return barcodeList;


}
