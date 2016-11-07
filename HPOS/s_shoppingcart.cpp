#include "s_shoppingcart.h"
#include "ui_shoppingCartScreen.h"

S_ShoppingCart *S_ShoppingCart::s_instance;


S_ShoppingCart *S_ShoppingCart::instance()
{
    if(!s_instance)
    {
        s_instance = new S_ShoppingCart();
    }
    return s_instance;
}

S_ShoppingCart::S_ShoppingCart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShoppingCartScreen)
{
    ui->setupUi(this);
}

S_ShoppingCart::~S_ShoppingCart()
{
    delete ui;
}
