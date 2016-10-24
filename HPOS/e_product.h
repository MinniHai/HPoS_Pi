#ifndef E_PRODUCT_H
#define E_PRODUCT_H
#include <QString>
#include <QList>
#include <QVariant>
#include "repository.h"

class E_Picture;
class E_Category;
class E_Barcode;


class E_Product : public Repository
{
public:
    static E_Product *getProductByID(QString ID);

    E_Product();
    E_Product *getResultSet();
    QList <E_Product *> getAllProduct();
    QString name;
    QString proID;
    double price;
    QString description;
    int pictureID;
    int quantity;

    E_Barcode *barcode;
    QList<E_Picture *> listPicture;
    E_Category *listCategory;
    QList<E_Barcode *> listBarcode;

};

#endif // E_PRODUCT_H
