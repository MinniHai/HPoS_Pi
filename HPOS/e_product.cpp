
#include "e_product.h"
#include "utils.h"
#include "e_picture.h"
#include "e_manufacturer.h"
#include "e_barcode.h"
#include "e_country.h"

E_Product::E_Product()
{

}
E_Product *E_Product::getResultSet()
{
    E_Product *product = new E_Product();
    product->name = query.value(query.record().indexOf("proName")).toString();
    product->proID = query.value(query.record().indexOf("proID")).toString();
    product->price = query.value(query.record().indexOf("proPrice")).toDouble();
    product->quantity = query.value(query.record().indexOf("quantity")).toInt();
    product->description = query.value(query.record().indexOf("proDes")).toString();
    //get list picture.
    product->listPicture = E_Picture::getPictureByProductID(product->proID);
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
        E_Product *product = (E_Product *)item;
        product->barcode = E_Barcode::getBarcodeByProID(product->proID);
        product->barcode->manufacturer = E_Manufacturer::getManufacturerByPrefix(product->barcode->manufacturerPrefix);
        product->barcode->country = E_Country::getCountryNameByPrefix(product->barcode->countryPrefix);
        listProduct.append(product);
    }
    return listProduct;

}
