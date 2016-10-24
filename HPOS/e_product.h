#ifndef E_PRODUCT_H
#define E_PRODUCT_H
#include <QString>
#include <QList>
#include <QVariant>
#include "repository.h"

class E_Picture;
class E_Category;


class E_Product : public Repository
{
public:
    static E_Product *getProductByID(QString ID);

    E_Product();
    E_Product *getResultSet();
    QList <E_Product *> getAllProduct();
    QString name;
    double price;
    QString description;
    int pictureID;
    int quantity;

    QList<E_Picture *> listPicture;
    QList<E_Category> *listCategory;
};

#endif // E_PRODUCT_H
