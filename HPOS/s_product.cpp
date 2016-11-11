#include "s_product.h"
#include "ui_productScreen.h"
#include <QScrollBar>
#include <QScroller>
#include "s_menu.h"
#include "s_manufacture.h"
#include "s_search.h"
#include "s_inventorymanager.h"
#include "s_checkout.h"

#include "e_barcode.h"
#include "e_manufacturer.h"
#include "e_category.h"
#include "e_product.h"
#include "e_country.h"
#include "e_picture.h"
#include "shoppingcart.h"

#include "barcodescanner.h"
#include "customeqlabel.h"
#include "utils.h"
#include <QMessageBox>
#include <QPushButton>

#include <QDir>
#include <QVariant>
#include <QDateTime>

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
    image->setAlignment(Qt::AlignCenter);
    image->setPixmap(QPixmap(":/images/images/camera.png").scaled(QSize(120, 120)));

    ui->cbCategory->addItem("");

    QRegExp date("(\\d\\d\\d\\d)");
    QRegExpValidator *dateVal = new QRegExpValidator(date);
    ui->ledQuantity->setValidator(dateVal);
    cateList = E_Category::getAllCategory();
    if(!cateList.isEmpty())
    {
        foreach(E_Category *item, cateList)
        {
            ui->cbCategory->addItem(item->categoryName, QVariant(item->ctID));
        }

    }
    QScrollArea *scrollArea = ui->scrollArea;
    scrollArea->setWidget(parent);
    QScroller::grabGesture(scrollArea, QScroller::TouchGesture);
    ui->cbProductName->setFixedSize(370, 40);
    ui->cbProductName->lineEdit()->setAlignment(Qt::AlignCenter);
    connect(ui->cbProductName, SIGNAL(currentIndexChanged(int)), SLOT(viewInformation(int)));
    connect(image, SIGNAL(clicked()), SLOT(capture()));
}

void S_Product::capture()
{

    BarcodeScanner *capturer = BarcodeScanner::instance();
    if(capturer->timer->isActive())
    {
        E_Picture *picture = new E_Picture();
        capturer->isCapture = true;
        picture->picUrl = capturer->imagePath;
        picture->proID = product->proID;
        QHash<QString, QString> pictureHash ;
        pictureHash.insert("picUrl", picture->picUrl);
        pictureHash.insert("proID", picture->proID);
        if(E_Picture::insertPicture(pictureHash))
        {
            if(!product->listPicture.isEmpty())
            {
                product->listPicture.append(picture);
                image->clear();
                image->setPixmap(QPixmap(QDir::rootPath() + product->listPicture.at(0)->picUrl).scaled(image->size()));
                image->repaint();
                image->show();
            }
        }
    }
    else
    {
        QString path  = "Image/Product/"
                + product->name
                + "_"
                + Utils::instance()->getCurrentDate()
                + "_"
                + Utils::instance()->getCurrentTime()
                + ".png";
        QDir dir("Image/Product");
        if(!dir.exists())
        {
            dir.mkpath(".");
        }
        capturer->capturePicture(path, image);
    }
}

void S_Product::setBarcode(E_Barcode *barcode)
{
    this->barcode = barcode;
    ui->cbProductName->clear();
    product = new E_Product();
    product->proID = E_Product::getMaxID().toInt() + 1;
    product->barcode = barcode;
    product->barcode->country = E_Country::getCountryByPrefix(product->barcode->countryPrefix);
    product->barcode->manufacturer = E_Manufacturer::getManufacturerByPrefix(product->barcode->manufacturerPrefix);
    ui->cbProductName->addItem(product->name);
    productList.clear();
    productList.append(product);
    foreach(E_Barcode *item, E_Barcode::getBarcodeByManuRefix(barcode->manufacturerPrefix))
    {
        E_Product *pro = E_Product::getProductByID(item->proID);
        productList.append(pro);
        ui->cbProductName->addItem(pro->name , QVariant(product->proID));
    }
    viewInformation(product);
}

void S_Product::setEnabled(bool isEnable)
{
    ui->cbProductName->setEnabled(isEnable);
    ui->cbCategory->setEnabled(isEnable);
    ui->btnAddManufacture->setEnabled(isEnable);
    ui->ledCountry->setEnabled(isEnable);
    ui->ledManufacture->setEnabled(isEnable);
    ui->ledPrice->setEnabled(isEnable);
    if(action != UpdateCart)
    {
        ui->ledQuantity->setEnabled(isEnable);
    }
    else
    {
        ui->ledQuantity->setEnabled(true);
    }
    ui->tetDescription->setEnabled(isEnable);
}

void S_Product::viewInformation(int currentIndext)
{
    if(!productList.isEmpty() && -1 < currentIndext && currentIndext < productList.size())
    {
        product = productList.at(currentIndext);
        viewInformation(product);
    }
}

void S_Product::viewInformation(E_Product *productTmp)
{
    this->product = productTmp;

    if(action == View || action == Update || action == UpdateCart)
    {
        ui->cbProductName->clear();
        ui->cbProductName->addItem(productTmp->name, QVariant(productTmp->proID));
        ui->ledQuantity->setText(QString::number(productTmp->quantity));
    }
    else
    {
        ui->cbProductName->setCurrentIndex(ui->cbProductName->findText(productTmp->name));
    }
    if(productTmp->price > 0)
    {
        ui->ledPrice->setText(QString::number(productTmp->price));
    }
    if(productTmp->barcode->country)
    {
        ui->ledCountry->setText(productTmp->barcode->country->name);
    }
    else
    {
        ui->ledCountry->setText("");
    }

    if(productTmp->barcode->manufacturer)
    {
        ui->ledManufacture->setText(productTmp->barcode->manufacturer->manuName);
    }
    else
    {
        ui->ledManufacture->setText("");
    }
    ui->tetDescription->setText(productTmp->description);

    if(productTmp->category)
    {
        ui->cbCategory->setCurrentIndex(ui->cbCategory->findText(productTmp->category->categoryName));
    }
    else
    {
        ui->cbCategory->setCurrentIndex(0);
    }

    if(!productTmp->listPicture.isEmpty())
    {
        image->clear();
        image->setPixmap(QPixmap(QDir::currentPath() + "/" + productTmp->listPicture.last()->picUrl).scaled(image->size()));
        image->repaint();
        image->show();
    }
}

void S_Product::clearAll()
{
    ui->ledCountry->setText("");
    ui->ledManufacture->setText("");
    ui->ledPrice->setText("");
    ui->ledQuantity->setText("");
    ui->tetDescription->setText("");
    ui->cbCategory->setCurrentIndex(0);
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
    S_Menu *menu = S_Menu::instance();
    menu->setModal(true);
    menu->showFull();
    this->close();
}

void S_Product::refreshManufacturer()
{
    ui->ledManufacture->setText(product->barcode->manufacturer->manuName);
}

void S_Product::on_btnAddManufacture_clicked()
{
    S_Manufacture *manufacture = S_Manufacture::instance();
    manufacture->setModal(true);
    manufacture->manufacturer = new E_Manufacturer();
    manufacture->manufacturer->manuPrefix = product->barcode->manufacturerPrefix;
    manufacture->fillData();
    manufacture->showFullScreen();
    this->close();
}

void S_Product::on_btnClear_clicked()
{
    if(product)
    {
        viewInformation(product);
    }
    else
    {
        clearAll();
    }
}

void S_Product::setQuantityText(int quantity)
{
    ui->ledQuantity->setText(QString::number(quantity));
}

void S_Product::on_btnSave_clicked()
{
    if(action == UpdateCart)
    {
        if(ui->ledQuantity->text().toInt() < product->quantity)
        {
            ShoppingCart::instance()->subTotal -= product->price * ShoppingCart::instance()->quantity[ShoppingCart::instance()->cart.indexOf(product)];
            ShoppingCart::instance()->quantity[ShoppingCart::instance()->cart.indexOf(product)] =
                    ui->ledQuantity->text().toInt();
            ShoppingCart::instance()->subTotal += product->price * ShoppingCart::instance()->quantity[ShoppingCart::instance()->cart.indexOf(product)];
            on_btnBack_clicked();
        }
        else
        {
            QMessageBox::warning(this, "Warning", "Not enough items for sale. Max: " + QString::number(product->quantity));
        }
    }
    else
    {
        QHash<QString, QString> proHash;
        proHash.insert("proName", ui->cbProductName->currentText());
        proHash.insert("proPrice", ui->ledPrice->text());
        proHash.insert("quantity", ui->ledQuantity->text());
        proHash.insert("ctID", ui->cbCategory->currentData().toString());
        proHash.insert("proDes", ui->tetDescription->toPlainText());
        if(action == Insert)
        {
            if(E_Product::insertProduct(proHash))
            {

                qDebug() << "Insert Product Ok";
                QHash<QString, QString> barcodeHash;
                barcodeHash.insert("countryPrefix", barcode->countryPrefix);
                barcodeHash.insert("manuPrefix", barcode->manufacturerPrefix);
                barcodeHash.insert("productPrefix", barcode->productPrefix);
                barcodeHash.insert("checkDigit", barcode->checkDigit);
                barcodeHash.insert("imDate", Utils::instance()->getCurrentDate());
                barcodeHash.insert("imTime", Utils::instance()->getCurrentTime());
                barcodeHash.insert("proID", E_Product::getMaxID());
                if(E_Barcode::insertBarcode(barcodeHash))
                {
                    qDebug() << "Insert Barcode Ok";
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
                    QMessageBox::warning(this, "Warning", "Something was wrong.");
                }
            }
            else
            {
                QMessageBox::warning(this, "Warning", "Something was wrong.");
            }
        }
        else if(action == Update)
        {
            if(E_Product::upateProduct(proHash, product->proID))
            {
                qDebug() << "Update Product : Ok";
                QMessageBox box ;
                box.setText("Update Done!");
                QPushButton *ok = box.addButton(QMessageBox::Ok);
                box.exec();
                if(box.clickedButton() == ok)
                {
                    on_btnBack_clicked();
                }
            }
            else
            {
                QMessageBox::warning(this, "Warning", "Something was wrong.");
            }
        }
        else if(action == InsertMore)
        {
            proHash.clear();
            proHash.insert("quantity", QString::number(ui->ledQuantity->text().toInt() + product->quantity));
            if(E_Product::upateProduct(proHash, product->proID))
            {
                qDebug() << "Insert more product : Ok";
            }
        }
    }
}
void S_Product::on_btnBack_clicked()
{
    if(action == UpdateCart)
    {
        S_Checkout *checkout = S_Checkout::instance();
        checkout->setModal(true);
        checkout->showDataToTable();
        checkout->showFullScreen();
        this->close();
    }
    else if(action != Update)
    {
        S_Search *searchScreen = S_Search::instance();
        searchScreen->setModal(true);
        searchScreen->setBackToDefaul();
        searchScreen->showFullScreen();
        this->close();
    }else
    {
        S_InventoryManager *inventoryScreen = S_InventoryManager::instance();
        inventoryScreen->setModal(true);
        inventoryScreen->showFullScreen();
        inventoryScreen->setDataToTable();
        this->close();
    }
}
