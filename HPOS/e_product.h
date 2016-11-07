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
    static QList <E_Product *> getProductByColumn(QString column, QString searchText);
    E_Product();
    E_Product *getResultSet();
    static QList <E_Product *> getAllProduct();
    static bool upateProduct(QHash<QString, QString> hash, QString productID);
    static bool deleteProduct(QString proID);
    static bool insertProduct(QHash<QString, QString> product);
    static QString getMaxID();

    QString name;
    QString proID;
    QString product;

    ulong price;
    QString description;
    int pictureID;
    int quantity;
    QString ctID;

    static QList<E_Product *> searchByColumn(QString column, QString searchText);



    E_Barcode *barcode;
    QList<E_Picture *> listPicture;
    E_Category *category;
    QList<E_Barcode *> listBarcode;

};

#endif // E_PRODUCT_H
