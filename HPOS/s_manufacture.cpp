#include "s_manufacture.h"
#include "ui_manufactureScreen.h"
#include "s_menu.h"
#include "e_manufacturer.h"
#include "s_product.h"
#include "e_product.h"
#include "e_barcode.h"
#include "barcodescanner.h"
#include <QDir>
#include <QMessageBox>
#include <QHash>
#include <QPushButton>

S_Manufacture *S_Manufacture::s_instance;


S_Manufacture *S_Manufacture::instance()
{
    if(!s_instance)
    {
        s_instance = new S_Manufacture();
    }
    return s_instance;
}

S_Manufacture::S_Manufacture(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Manufacture)
{
    ui->setupUi(this);
    manufacturer = new E_Manufacturer();
    image = new  CustomeQlabel("", ui->frame_4);
    image->setObjectName("image");
    image->setGeometry(0, 0, 181, 181);
    image->setAlignment(Qt::AlignCenter);

    connect(image, SIGNAL(clicked()), SLOT(capture()));
}


void S_Manufacture::capture()
{
    BarcodeScanner *capturer = BarcodeScanner::instance();
    if(capturer->timer->isActive())
    {
        capturer->isCapture = true;
        manufacturer->logoUrl = capturer->imagePath;
    }
    else
    {

        QString path ;
        if(!manufacturer->manuPrefix.isEmpty())
        {
            path = "Image/Manufacturer/"
                   + manufacturer->manuPrefix
                   + ".png";
        }
        else
        {
            path = "Image/Manufacturer/tmp.png";
        }
        QDir dir("Image/Manufacturer");
        if(!dir.exists())
        {
            dir.mkpath(".");
        }
        capturer->capturePicture(path, image);
    }
}

void S_Manufacture::fillData()
{
    ui->ledPrefix->setText(manufacturer->manuPrefix);
    image->setPixmap(QPixmap(":/images/images/camera.png").scaled(QSize(120, 120)));
}

S_Manufacture::~S_Manufacture()
{
    delete ui;
}

void S_Manufacture::on_btnMenu_clicked()
{
    S_Menu *menu = S_Menu::instance();
    menu->setModal(true);
    menu->showFull();
    this->close();
}

void S_Manufacture::on_btnSave_clicked()
{
    if(!ui->ledName->text().isEmpty())
    {
        QHash<QString , QString > manuHash;
        manuHash.insert("manuPrefix", ui->ledPrefix->text());
        manuHash.insert("manuName", ui->ledName->text());
        manufacturer->manuName = ui->ledName->text();
        manuHash.insert("address", ui->ledAddress->text());
        manufacturer->address  =  ui->ledAddress->text();
        manuHash.insert("phone", ui->ledPhoneNumber->text());
        manufacturer->phone = ui->ledPhoneNumber->text();
        manuHash.insert("logoUrl", manufacturer->logoUrl);
        if(E_Manufacturer::insertManufacturer(manuHash))
        {
            QMessageBox box ;
            box.setText("Insert Done!");
            QPushButton *ok = box.addButton(QMessageBox::Ok);
            box.exec();
            if(box.clickedButton() == ok)
            {
                on_btnBack_clicked();
            }
        }
        else
        {
            QMessageBox::information(this, "Insert ", "Insert Failed!");

        }
    }
    else
    {
        QMessageBox::warning(this, "Warning", "You must fill manufacturer name.");
    }
}

void S_Manufacture::on_btnBack_clicked()
{
    S_Product *productScreen = S_Product::instance();
    productScreen->product->barcode->manufacturer = manufacturer;
    //    productScreen->action = S_Product::View;
    //    productScreen->setEnabled(false);
    productScreen->refreshManufacturer();
    productScreen->showFullScreen();
    this->close();
    BarcodeScanner::instance()->releaseCam();
}
