#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <QHash>
#include <QList>

class E_Product;
class ShoppingCart
{
public:
    static ShoppingCart *s_instance;
    static ShoppingCart *instance();
    ShoppingCart();

    ulong tax;
    ulong total;
    ulong subTotal;
    QList<E_Product *> cart;
    QList<int> quantity;
    void addCart(E_Product *, int);
    void cancelCart();
    void removeCart(E_Product *product);
    bool saveCarts();
};

#endif // SHOPPINGCART_H
