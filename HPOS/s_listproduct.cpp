#include "s_listproduct.h"
#include "ui_shoppingCartScreen.h"

S_ListProduct::S_ListProduct(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ListProduct)
{
    ui->setupUi(this);
}

S_ListProduct::~S_ListProduct()
{
    delete ui;
}
