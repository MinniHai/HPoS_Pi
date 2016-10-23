#include "shoppingcart.h"
#include "e_product.h"

ShoppingCart *ShoppingCart::s_instance;

ShoppingCart::ShoppingCart()
{
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
    if(product)
    {
        if(cart.contains(product))
        {
            quantity = cart.value(product) + quantity;
        }
        cart.insert(product, quantity);
    }
}
