#include "s_shoppingcart.h"
#include "ui_shoppingCartScreen.h"

S_ShoppingCart::S_ShoppingCart(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShoppingCart)
{
    ui->setupUi(this);
}

S_ShoppingCart::~S_ShoppingCart()
{
    delete ui;
}
