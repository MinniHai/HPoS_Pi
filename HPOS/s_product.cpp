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
#include <QFrame>
#include <QAbstractItemView>
#include <QScrollBar>
#include <session.h>

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

    ledPrice = new CustomeLineEdit(ui->frame);
    ledPrice->setGeometry(0,179,154,62);
    ledPrice->setObjectName("ledPrice");
    ledPrice->setAlignment(Qt::AlignRight);
    QLabel *priceLabel = new QLabel(ui->frame);
    priceLabel->setGeometry(120,187,28,51);
    priceLabel->setStyleSheet("color: rgb(255, 255, 255);");
    priceLabel->setText("VND");

    ui->cbProductName->setGeometry(70,0,350,40);
    ui->cbProductName->setEditable(true);
    ui->cbProductName->lineEdit()->setAlignment(Qt::AlignCenter);

    //    connect(ui->cbProductName, SIGNAL(currentIndexChanged(int)), SLOT(viewInformation(int)));

    connect(image, SIGNAL(clicked()), SLOT(capture()));

    connect(ledPrice, SIGNAL(selectionChanged()), SLOT(runKeyboard()));
    lineName = ui->cbProductName->lineEdit();
    lineName->setPlaceholderText("Name Of Product");
    fillLayout();
}

void S_Product::fillLayout(){

    QWidget *widget = new QWidget();

    QGridLayout *grid = new QGridLayout();

    ledCountry = new CustomeLineEdit();
    ledManufacture = new CustomeLineEdit();
    ledBarcode = new QLineEdit();
    ledBarcode->setDisabled(true);
    ledQuantity = new CustomeLineEdit();
    ledQuantity->setClearButtonEnabled(true);
    btnAddManufacture = new QToolButton();
    btnAddManufacture->setObjectName("btnAddManufacture");
    btnAddManufacture->setFixedWidth(29);
    btnAddManufacture->setText("+");
    cbCategory = new QComboBox();
    QAbstractItemView *cvView1 = cbCategory->view();
    cvView1->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    cbCategory->setStyleSheet("combobox-popup: 0;");
    cbCategory->setMaxVisibleItems(4);
    QRegExp date1("(\\d\\d\\d\\d)");
    QRegExpValidator *dateVal1 = new QRegExpValidator(date1);
    ledQuantity->setValidator(dateVal1);
    cateList = E_Category::getAllCategory();
    if(!cateList.isEmpty())
    {
        foreach(E_Category *item, cateList)
        {
            cbCategory->addItem(item->categoryName, QVariant(item->ctID));
        }

    }
    lbCost = new QLabel("Cost");
    ledCost  = new CustomeLineEdit();
    lbBarcode = new QLabel("Barcode");


    grid->addWidget(new QLabel("Category"),0,0,1,1);
    grid->addWidget(cbCategory,1,0,1,2);
    grid->addWidget(lbCost,2,0);
    grid->addWidget(ledCost,3,0,1,2);
    grid->addWidget(new QLabel("Quantity"),4,0);
    grid->addWidget(ledQuantity,5,0,1,2);
    grid->addWidget(new QLabel("Country"),6,0);
    grid->addWidget(ledCountry,7,0,1,2);
    grid->addWidget(new QLabel("Manufacturer"),8,0);
    grid->addWidget(ledManufacture,9,0);
    grid->addWidget(btnAddManufacture,9,1);
    grid->addWidget(lbBarcode,10,0,1,2);
    grid->addWidget(ledBarcode,11,0,1,2);
    connect(btnAddManufacture,SIGNAL(pressed()),SLOT(btnAddManufacture_click()));
    widget->setLayout(grid);
    ui->scrollArea->setWidget(widget);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->scrollArea->verticalScrollBar()->setStyleSheet(
                "QScrollBar:vertical { width: 15; }");
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

void S_Product::setProductInsert(E_Product *pro)
{
    disconnect(ui->cbProductName, SIGNAL(currentIndexChanged(int)),this, SLOT(viewInformation(int)));
    ui->cbProductName->clear();

    product = pro;
    product->proID = E_Product::getMaxID().toInt() + 1;
    product->barcode->country = E_Country::getCountryByPrefix(product->barcode->countryPrefix);
    product->barcode->manufacturer = E_Manufacturer::getManufacturerByPrefix(product->barcode->manufacturerPrefix);
    ui->cbProductName->addItem(product->name);
    productList.clear();
    productList.append(product);

    foreach(E_Barcode *item, E_Barcode::getBarcodeByManuRefix(product->barcode->manufacturerPrefix))
    {
        E_Product *pro = E_Product::getProductByID(item->proID);
        productList.append(pro);
        ui->cbProductName->addItem(pro->name , QVariant(product->proID));
    }
    viewInformation(product);
    connect(ui->cbProductName, SIGNAL(currentIndexChanged(int)), SLOT(viewInformation(int)));
}

void S_Product::setEnabled(bool isEnable)
{
    ui->cbProductName->setEnabled(isEnable);
    cbCategory->setEnabled(isEnable);
    btnAddManufacture->setEnabled(isEnable);

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
        if(action == Insert) {
            changeInformation(product);
        } else
            viewInformation(product);
    }
}

void S_Product::changeInformation(E_Product *productTmp){
    if(!productTmp->name.isEmpty()) {
        ledCost->setText(QString::number(productTmp->barcode->cost));
        ledPrice->setText(QString::number(productTmp->price));
        cbCategory->setCurrentIndex(cbCategory->findText(productTmp->category->categoryName));
    } else {
        ledCost->setText("");
        ledPrice->setText("");
    }
}

void S_Product::viewInformation(E_Product *productTmp)
{
    ledCountry->setEnabled(true);
    ledManufacture->setEnabled(true);

    ledBarcode->setText(productTmp->barcode->barcode);
    if(action == Insert || action == InsertMore || action == Update) {
        ui->btnKeyboard->setVisible(true);
        lbCost->setVisible(true);
        ledCost->setVisible(true);
        ledCost->setText(QString::number(productTmp->barcode->cost));
    } else {
        lbCost->setVisible(false);
        ledCost->setVisible(false);
        ui->btnKeyboard->setVisible(false);
    }
    this->product = productTmp;
    if(action == View || action == Update)
    {
        ledQuantity->setText(QString::number(productTmp->quantity));
    }else if(action == UpdateCart){
        ledQuantity->setText(QString::number(ShoppingCart::instance()->quantity[ShoppingCart::instance()->cart.indexOf(productTmp)]));
    }
    else {
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
    } else {
        ledPrice->setText("");
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
    ledCountry->setEnabled(false);
    ledManufacture->setEnabled(false);
    image->setFocus();
}

void S_Product::clearAll()
{
    ledPrice->setText("");
    ledQuantity->setText("1");
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
    if(!product->name.isEmpty() && action != Insert)
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

        proHash.insert("ctID", cbCategory->currentData().toString());
        //        proHash.insert("proDes", ui->tetDescription->toPlainText());
        QHash<QString, QString> barcodeHash;
        if(action == Insert)
        {
            if(product->name.isEmpty()) {
                proHash.insert("quantity", QString::number(ledQuantity->text().toInt()));
                if(E_Product::insertProduct(proHash))
                {
                    barcodeHash.insert("countryPrefix", product->barcode->countryPrefix);
                    barcodeHash.insert("manuPrefix", product->barcode->manufacturerPrefix);
                    barcodeHash.insert("productPrefix", product->barcode->productPrefix);
                    barcodeHash.insert("checkDigit", product->barcode->checkDigit);
                    barcodeHash.insert("imDate", Utils::instance()->getCurrentDate());
                    barcodeHash.insert("imTime", Utils::instance()->getCurrentTime());
                    barcodeHash.insert("proID", E_Product::getMaxID());
                    barcodeHash.insert("cost",ledCost->text());
                    barcodeHash.insert("quantity",ledQuantity->text());
                    qDebug() << "Insert Product Ok";
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
            } else {
                proHash.insert("quantity", QString::number((ledQuantity->text().toInt() + product->quantity)));
                barcodeHash.insert("countryPrefix", barcode->countryPrefix);
                barcodeHash.insert("manuPrefix", barcode->manufacturerPrefix);
                barcodeHash.insert("productPrefix", barcode->productPrefix);
                barcodeHash.insert("checkDigit", barcode->checkDigit);
                barcodeHash.insert("imDate", Utils::instance()->getCurrentDate());
                barcodeHash.insert("imTime", Utils::instance()->getCurrentTime());
                barcodeHash.insert("proID", E_Product::getMaxID());
                barcodeHash.insert("cost",ledCost->text());
                barcodeHash.insert("quantity",ledQuantity->text());
                qDebug() << "Insert Product Ok";
                if(E_Barcode::insertBarcode(barcodeHash))
                {
                    if(E_Product::upateProduct(proHash, product->proID))
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
                    }else
                    {
                        QMessageBox::warning(this, "Warning", "Something was wrong.");
                    }
                }
                else
                {
                    QMessageBox::warning(this, "Warning", "Something was wrong.");
                }
            }
        }
        else if(action == Update)
        {
            proHash.insert("quantity", ledQuantity->text());
            if(E_Product::upateProduct(proHash, product->proID))
            {

//                proHash.insert("quantity", ledQuantity->text() + product->quantity);
                barcodeHash.insert("cost",ledCost->text());
                barcodeHash.insert("quantity",ledQuantity->text());

                if(E_Barcode::upateBarcode(barcodeHash,QString::number(product->barcode->barcodeID)))
                {
                    qDebug() << "Update Product : Ok";
                    QMessageBox box ;
                    box.setText("Update Done!");
                    QPushButton *ok = box.addButton(QMessageBox::Ok);
                    box.exec();
                    if(box.clickedButton() == ok)
                    {
                        E_Barcode::upateBarcode(barcodeHash,product->barcode->countryPrefix
                                                ,product->barcode->productPrefix,product->barcode->manufacturerPrefix);
                        on_btnBack_clicked();
                    }
                }else
                {
                    QMessageBox::warning(this, "Warning", "Something was wrong.");
                }
            }
            else
            {
                QMessageBox::warning(this, "Warning", "Something was wrong.");
            }
        }
        else if(action == InsertMore)
        {
            proHash.insert("quantity", QString::number(ledQuantity->text().toInt() + product->quantity));
            if(E_Product::upateProduct(proHash, product->proID))
            {
                barcodeHash.insert("cost",ledCost->text());
                barcodeHash.insert("quantity",QString::number(ledQuantity->text().toInt() + product->quantity));
                E_Barcode::upateBarcode(barcodeHash,product->barcode->countryPrefix,product->barcode->productPrefix
                                        ,product->barcode->manufacturerPrefix);

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
        searchScreen->showFullScreen();
        this->close();
    }else
    {
        S_InventoryManager *inventoryScreen = S_InventoryManager::instance();
        inventoryScreen->setModal(true);
        inventoryScreen->listProduct = E_Product::getAllProduct();
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
