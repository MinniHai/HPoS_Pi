#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <QHash>

class E_Product;
class ShoppingCart
{
public:
    static ShoppingCart *s_instance;
    static ShoppingCart *instance();
    ShoppingCart();

    QHash<E_Product *, int> cart;
    void addCart(E_Product *, int);
};

#endif // SHOPPINGCART_H
