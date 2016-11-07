
#include "e_product.h"
#include "utils.h"
#include "e_picture.h"
#include "e_manufacturer.h"
#include "e_barcode.h"
#include "e_country.h"
#include "e_category.h"
#include "e_state.h"


E_Product::E_Product()
{
    category = NULL;
    barcode = NULL;
    price = 0;
    name = "";
}
E_Product *E_Product::getResultSet()
{
    E_Product *product = new E_Product();
    product->name = query.value(query.record().indexOf("proName")).toString();
    product->proID = query.value(query.record().indexOf("proID")).toString();
    product->ctID = query.value(query.record().indexOf("ctID")).toString();
    product->price = query.value(query.record().indexOf("proPrice")).toLongLong();
    product->quantity = query.value(query.record().indexOf("quantity")).toInt();
    product->description = query.value(query.record().indexOf("proDes")).toString();
    //get list picture.
    product->listPicture = E_Picture::getPictureByProductID(product->proID);

    product->barcode = E_Barcode::getBarcodeByProID(product->proID);

    product->category = E_Category::getCategoryByID(product->ctID);
    return product;
}

QString E_Product::getMaxID()
{
    Repository *repository = new E_Product();
    repository->setSelectQuery("MAX(proID)", "Product");
    if(repository->query.exec())
    {
        if(repository->query.next())
        {
            return repository->query.value(repository->query.record().indexOf("MAX(proID)")).toString();
        }
    }
    return "";
}

E_Product *E_Product::getProductByID(QString ID)
{
    Repository *productRepo = new E_Product();
    productRepo->setSelectQuery("*", "Product", "proID", ID);
    return (E_Product *)productRepo->getEntityByQuery();
}

QList<E_Product *> E_Product::getAllProduct()
{
    QList <E_Product *> listProduct;

    Repository *productRepo = new E_Product();
    productRepo->setSelectQuery("*", "Product");
    foreach(Repository *item, productRepo->getListEntityByQuery())
    {
        E_Product *product = (E_Product *)item;

        listProduct.append(product);
    }
    return listProduct;

}
QList <E_Product *> E_Product::getProductByColumn(QString column, QString searchText)
{
    QList <E_Product *> listProduct;
    Repository *productRepo = new E_Product();
    productRepo->setSelectQuery("*", "Product", column, searchText);
    foreach(Repository *item, productRepo->getListEntityByQuery())
    {
        listProduct.append((E_Product *)item);
    }
    return listProduct;
}

QList<E_Product *> E_Product::searchByColumn(QString column, QString searchText)
{
    QList <E_Product *> listProduct;
    Repository *productRepo = new E_Product();
    productRepo->setSelectLikeQuery("*", "Product", column, searchText);
    foreach(Repository *item, productRepo->getListEntityByQuery())
    {
        listProduct.append((E_Product *)item);
    }
    return listProduct;
}

bool E_Product::insertProduct(QHash<QString, QString> product)
{
    Repository *proRepo = new E_Product();
    proRepo->setInsertQuery("Product", product);
    return proRepo->query.exec();
}

bool E_Product::upateProduct(QHash<QString, QString> hash, QString productID)
{
    Repository *productRepo = new E_Product();
    productRepo->setUpdateQuery("Product", hash, "proID", productID);
    return productRepo->query.exec();
}

bool E_Product::deleteProduct(QString proID)
{
    Repository *userRepo = new E_Product();
    userRepo->setDeleteQuery("Product", "proID", proID);
    return userRepo->query.exec();
}
