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
#include "keyboard.h"

#include <QMessageBox>
#include <QPushButton>

#include <QDir>
#include <QVariant>
#include <QDateTime>
#include <QGridLayout>

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
    ledCountry = new CustomeLineEdit();
    ledManufacture = new CustomeLineEdit();

    ledPrice = new CustomeLineEdit(ui->frame);
    ledPrice->setGeometry(0,179,154,62);
    ledPrice->setObjectName("ledPrice");
    ledPrice->setAlignment(Qt::AlignRight);
    QLabel *priceLabel = new QLabel(ui->frame);
    priceLabel->setGeometry(120,187,28,51);
    priceLabel->setStyleSheet("color: rgb(255, 255, 255);");
    priceLabel->setText("VND");

    ledQuantity = new CustomeLineEdit();
    btnAddManufacture = new QToolButton();
    btnAddManufacture->setObjectName("btnAddManufacture");
    btnAddManufacture->setFixedWidth(29);
    btnAddManufacture->setText("+");
    cbCategory = new QComboBox();
//    cbCategory->addItem("");

    QRegExp date("(\\d\\d\\d\\d)");
    QRegExpValidator *dateVal = new QRegExpValidator(date);
    ledQuantity->setValidator(dateVal);
    cateList = E_Category::getAllCategory();
    if(!cateList.isEmpty())
    {
        foreach(E_Category *item, cateList)
        {
            cbCategory->addItem(item->categoryName, QVariant(item->ctID));
        }

    }
    QScrollArea *scrollArea = ui->scrollArea;
    scrollArea->setWidget(parent);
    QScroller::grabGesture(scrollArea, QScroller::TouchGesture);

//    ui->cbProductName = new CustomeComboBox(ui->frame_3);
    ui->cbProductName->setGeometry(70,0,350,40);
    ui->cbProductName->setEditable(true);
//    ui->cbProductName->setObjectName("ui->cbProductName");
    cbPro = (CustomeLineEdit *)ui->cbProductName->lineEdit();
//    ui->cbProductName->setFixedSize(370, 40);
    ui->cbProductName->lineEdit()->setAlignment(Qt::AlignCenter);
    connect(ui->cbProductName, SIGNAL(currentIndexChanged(int)), SLOT(viewInformation(int)));

    connect(btnAddManufacture,SIGNAL(pressed()),SLOT(btnAddManufacture_click()));
    connect(image, SIGNAL(clicked()), SLOT(capture()));

//    connect(ledCountry, SIGNAL(selectionChanged()), SLOT(runKeyboard()));
//    connect(ledManufacture, SIGNAL(selectionChanged()), SLOT(runKeyboard()));
//    connect(ledQuantity, SIGNAL(selectionChanged()), SLOT(runKeyboard()));

    connect(ledPrice, SIGNAL(selectionChanged()), SLOT(runKeyboard()));
//    connect(ui->tetDescription, SIGNAL(selectionChanged()), SLOT(runKeyboard()));
    lineName = ui->cbProductName->lineEdit();
    lineName->setPlaceholderText("Name Of Product");
    fillLayout();
}

void S_Product::fillLayout(){

    QGridLayout *grid = new QGridLayout();

    grid->addWidget(new QLabel("Quantity"),0,0);
    grid->addWidget(ledQuantity,1,0);
    grid->addWidget(new QLabel("Country"),2,0);
    grid->addWidget(ledCountry,3,0);
    grid->addWidget(new QLabel("Manufacturer"),4,0);
    grid->addWidget(ledManufacture,5,0);
    grid->addWidget(btnAddManufacture,5,1);

    grid->addWidget(new QLabel("Category"),6,0);
    grid->addWidget(cbCategory,7,0);
    ui->scrollArea->setLayout(grid);
}

void S_Product::capture()
{
    if(action == Update || action == Insert || action == InsertMore) {
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
    cbCategory->setEnabled(isEnable);
    btnAddManufacture->setEnabled(isEnable);
    ledCountry->setEnabled(isEnable);
    ledManufacture->setEnabled(isEnable);
    ledPrice->setEnabled(isEnable);
    if(action != UpdateCart)
    {
        ledQuantity->setEnabled(isEnable);
    }
    else
    {
        ledQuantity->setEnabled(true);
    }
//    ui->tetDescription->setEnabled(isEnable);
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
    if(action == Insert || action == InsertMore || action == Update) {
        ui->btnKeyboard->setVisible(true);
    } else {
        ui->btnKeyboard->setVisible(false);
    }
    this->product = productTmp;
    if(action == View || action == Update || action == UpdateCart)
    {
        ledQuantity->setText(QString::number(productTmp->quantity));
    } else {
        ledQuantity->setText(QString::number(1));
    }

    if(action == View || action == Update || action == UpdateCart || action == InsertMore)
    {
        ui->cbProductName->clear();
        ui->cbProductName->addItem(productTmp->name, QVariant(productTmp->proID));
        qDebug() << productTmp->name;
    }
    else
    {
        ui->cbProductName->setCurrentIndex(ui->cbProductName->findText(productTmp->name));
    }
    if(productTmp->price > 0)
    {
        ledPrice->setText(QString::number(productTmp->price));
    }
    if(productTmp->barcode->country)
    {
        ledCountry->setText(productTmp->barcode->country->name);
    }
    else
    {
        ledCountry->setText("");
    }

    if(productTmp->barcode->manufacturer)
    {
        ledManufacture->setText(productTmp->barcode->manufacturer->manuName);
    }
    else
    {
        ledManufacture->setText("");
    }
//    ui->tetDescription->setText(productTmp->description);

    if(productTmp->category)
    {
        cbCategory->setCurrentIndex(cbCategory->findText(productTmp->category->categoryName));
    }
    else
    {
        cbCategory->setCurrentIndex(0);
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
    ledCountry->setText("");
    ledManufacture->setText("");
    ledPrice->setText("");
    ledQuantity->setText("");
//    ui->tetDescription->setText("");
    cbCategory->setCurrentIndex(0);
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
    ledManufacture->setText(product->barcode->manufacturer->manuName);
}

void S_Product::btnAddManufacture_click()
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
    ledQuantity->setText(QString::number(quantity));
}

void S_Product::on_btnSave_clicked()
{
    if(action == UpdateCart)
    {
        if(ledQuantity->text().toInt() < product->quantity)
        {
            ShoppingCart::instance()->subTotal -= product->price * ShoppingCart::instance()->quantity[ShoppingCart::instance()->cart.indexOf(product)];
            ShoppingCart::instance()->quantity[ShoppingCart::instance()->cart.indexOf(product)] =
                    ledQuantity->text().toInt();
            ShoppingCart::instance()->subTotal += product->price * ShoppingCart::instance()->quantity[ShoppingCart::instance()->cart.indexOf(product)];
            on_btnBack_clicked();
        }
        else
        {
            QMessageBox::warning(this, "Warning", "Not enough items for sale. Max: " + QString::number(product->quantity));
        }
    }
    else if(ledPrice->text().toInt() > 0)
    {
        QHash<QString, QString> proHash;
        proHash.insert("proName", ui->cbProductName->currentText());
        proHash.insert("proPrice", ledPrice->text());
        proHash.insert("quantity", ledQuantity->text());
        proHash.insert("ctID", cbCategory->currentData().toString());
//        proHash.insert("proDes", ui->tetDescription->toPlainText());
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
            proHash.insert("quantity", QString::number(ledQuantity->text().toInt() + product->quantity));
            if(E_Product::upateProduct(proHash, product->proID))
            {
                qDebug() << "Insert more product : Ok";
                QMessageBox box ;
                box.setText("Insert more product :Done!");
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
    } else {
        QMessageBox::warning(this, "Warning", "Quantity must be larger than 0.");
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
//        searchScreen->setBackToDefaul();
        searchScreen->showFullScreen();
        this->close();
    }else
    {
        S_InventoryManager *inventoryScreen = S_InventoryManager::instance();
        inventoryScreen->setModal(true);
        inventoryScreen->setDataToTable();
        inventoryScreen->showFullScreen();
        this->close();
    }
}

void S_Product::runKeyboard()
{
    QLineEdit *line = (QLineEdit *)sender();
    Keyboard *keyboard = Keyboard::instance();
    keyboard->setLineEdit(line);
    keyboard->showFullScreen();
}

void S_Product::on_btnKeyboard_clicked()
{
    QLineEdit *line = lineName;
    Keyboard *keyboard = Keyboard::instance();
    keyboard->setLineEdit(line);

    keyboard->showFullScreen();
}
