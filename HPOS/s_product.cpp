#include "s_product.h"
#include "ui_productScreen.h"
#include <QScrollBar>
#include <QScroller>
#include "s_menu.h"
#include "s_manufacture.h"
#include "customeqlabel.h"
#include "e_product.h"

S_Product *S_Product::s_instance;
S_Product *S_Product::instance()
{
    if(!s_instance)
    {
        s_instance = new S_Product();
    }
    return s_instance;
}


S_Product::S_Product(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Product)
{
    ui->setupUi(this);
    product = new E_Product();
    image = new CustomeQlabel("", ui->frame);
    image->setGeometry(0, 0, 151, 181);
    image->setObjectName("image");

    QScrollArea *scrollArea = ui->scrollArea;
    scrollArea->setWidget(parent);
    QScroller::grabGesture(scrollArea, QScroller::TouchGesture);
    ui->cbProductName->setFixedSize(370, 40);
    setEnabled(false);
}

void S_Product::setEnabled(bool isEnable)
{
    ui->cbProductName->setEnabled(isEnable);
    ui->btnAddManufacture->setEnabled(isEnable);
    ui->ledCountry->setEnabled(isEnable);
    ui->ledManufacture->setEnabled(isEnable);
    ui->ledPrice->setEnabled(isEnable);
    ui->ledQuantity->setEnabled(isEnable);
    ui->tetDescription->setEnabled(isEnable);
}

void S_Product::viewInformation(E_Product *product)
{
    ui->cbProductName->addItem(product->name);
    //    ui->ledCountry->setText();
}

S_Product::~S_Product()
{
    delete ui;
}

void S_Product::setProduct(E_Product *product)
{
    if(product != NULL)
    {
        this->product = product;
    }
}

void S_Product::on_btnMenu_clicked()
{
    this->close();
    S_Menu menu;
    menu.setModal(true);
    menu.showFullScreen();
    menu.exec();
}

void S_Product::on_btnAddManufacture_clicked()
{
    this->hide();
    S_Manufacture manufacture;
    manufacture.setModal(true);
    manufacture.showFullScreen();
    manufacture.exec();

}
