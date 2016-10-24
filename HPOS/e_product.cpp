
#include "e_product.h"
#include "utils.h"
E_Product::E_Product()
{

}
E_Product *E_Product::getResultSet()
{
    E_Product *product = new E_Product();
    product->name = query.value(query.record().indexOf("proName")).toString();
    product->price = query.value(query.record().indexOf("proPrice")).toDouble();
    product->quantity = query.value(query.record().indexOf("quantity")).toInt();
    //product->description = query.value(query.record().indexOf("proDes")).toString();
    return product;
}

E_Product *E_Product::getProductByID(QString ID)
{
    Repository *productRepo = new E_Product();
    productRepo->setSelectQuery("*", "product", "proID", ID);
    return (E_Product *)productRepo->getEntityByQuery();
}

QList<E_Product *> E_Product::getAllProduct()
{
    QList <E_Product *> listProduct;

    Repository *productRepo = new E_Product();
    productRepo->setSelectQuery("*", "Product");
    foreach(Repository *item, productRepo->getListEntityByQuery())
    {
        listProduct.append((E_Product *)item);
    }
    return listProduct;

}
