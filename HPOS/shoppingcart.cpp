#include "shoppingcart.h"
#include "e_product.h"
#include "e_invoice.h"
#include "e_invoicedetail.h"
#include "e_barcode.h"

#include "session.h"
#include "utils.h"
#include <QHash>


ShoppingCart *ShoppingCart::s_instance;

ShoppingCart::ShoppingCart()
{
    subTotal = 0;
    total = 0;
    tax = 0;
}

ShoppingCart *ShoppingCart::instance()
{
    if(!s_instance)
    {
        s_instance = new ShoppingCart();
    }
    return s_instance;
}

void ShoppingCart::addCart(E_Product *product, int quantity)
{
    bool isContains = false;
    if(product)
    {
        subTotal +=  product->price * quantity;
        for(int i = 0; i < cart.size(); i ++)
        {
            E_Product *pro  = cart.at(i);
            if(pro->proID == product->proID)
            {
                isContains = true;
                this->quantity[i] = (this->quantity.at(i)) + quantity;
                break;
            }
        }
        if(!isContains)
        {
            cart.append(product);
            this->quantity.append(quantity);
        }
    }
}

void ShoppingCart::removeCart(E_Product *product)
{
    if(cart.contains(product))
    {
        subTotal -= cart[cart.indexOf(product)]->price * quantity[(cart.indexOf(product))];
        quantity.removeAt(cart.indexOf(product));
        cart.removeAt(cart.indexOf(product));
    }
}


void ShoppingCart::cancelCart()
{
    subTotal = 0;
    total = 0;
    cart.clear();
    quantity.clear();
}

bool ShoppingCart::saveCarts()
{
    total = subTotal;
    QHash<QString , QString> invoice;
    invoice.insert("userID", Session::instance()->getUserSession()->userID);
    invoice.insert("ivDate", Utils::instance()->getCurrentDate());
    invoice.insert("ivTime", Utils::instance()->getCurrentTime());
    invoice.insert("subtotal", QString::number(subTotal));
    invoice.insert("total", QString::number(total));
    if(E_Invoice::insertInvoice(invoice))
    {
        for(int i = 0; i < cart.size(); i++)
        {
            E_Product *item = cart[i];
            int qty = quantity[i];
            QList<E_Barcode *> barlist = E_Barcode::getAllBarcodeSortedByProID(item->proID);

            foreach (E_Barcode *barItem, barlist) {

                if(qty < barItem->quantity)
                {
                    QHash<QString, QString> ivDetail;
                    ivDetail.insert("ivID", E_Invoice::getMaxID());
                    ivDetail.insert("barcodeID", QString::number(barItem->barcodeID));
                    ivDetail.insert("quantity", QString::number(qty));
                    ivDetail.insert("subtotal", QString::number(item->price * (qty)));

                    if(!E_InvoiceDetail::insertIvDetail(ivDetail))
                    {
                        return false;
                    }
                    else
                    {
                        QHash <QString , QString> product;
                        product.insert("quantity", QString::number(item->quantity -qty));
                        if(E_Product::upateProduct(product, item->proID))
                        {
                            QHash <QString , QString> bar;
                            bar.insert("quantity", QString::number(barItem->quantity - qty));
                            if(!E_Barcode::upateBarcode(bar,QString::number(barItem->barcodeID))){
                                return false;
                            }
                        }
                    }
                } else {

                    QHash<QString, QString> ivDetail;
                    ivDetail.insert("ivID", E_Invoice::getMaxID());
                    ivDetail.insert("barcodeID", QString::number(barItem->barcodeID));
                    ivDetail.insert("quantity", QString::number(barItem->quantity));
                    ivDetail.insert("subtotal", QString::number(item->price * (barItem->quantity)));

                    if(!E_InvoiceDetail::insertIvDetail(ivDetail))
                    {
                        return false;
                    }
                    else
                    {
                        qty = qty - barItem->quantity;
                        QHash <QString , QString> product;
                        product.insert("quantity", QString::number(item->quantity -  qty));
                        if(E_Product::upateProduct(product, item->proID))
                        {
                            QHash <QString , QString> bar;
                            bar.insert("quantity", QString::number(0));
                            if(!E_Barcode::upateBarcode(bar,QString::number(barItem->barcodeID))){
                                return false;
                            }
                        }
                    }
                }
            }
        }
        return true;
    }
    return false;
}
