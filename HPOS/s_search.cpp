#include "s_search.h"
#include "s_menu.h"

#include <QString>
#include <QIcon>
#include "e_barcode.h"
#include "e_product.h"
#include "e_picture.h"
#include "s_product.h"
#include "barcodescanner.h"
#include "shoppingcart.h"
#include "ui_searchScreen.h"
#include <ui_checkoutScreen.h>
#include "s_checkout.h"
#include "keyboard.h"
#include <QLabel>
#include <QMessageBox>
#include <QIntValidator>
#include "customeqlabel.h"
#include "s_inventorymanager.h"
#include "wiringPi.h"
#include <QToolButton>

using namespace std;

#define BUTTON_OK 29
#define BUTTON_NO 28

E_Barcode *e_barcode;

S_Search *S_Search::s_instance;
bool isOKDown;
bool isNODown;
bool isEnableBt;


S_Search *S_Search::instance()
{
    if(!s_instance)
    {
        s_instance = new S_Search();
    }
    return s_instance;
}

S_Search::S_Search(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Search)
{
    ui->setupUi(this);
    bc = new BarcodeScanner();
    txtSearch = new QLineEdit();
    timer = new QTimer(this);
    lbStatus = new CustomeQlabel("", ui->frame_2);
    lbStatus->setObjectName("lbStatus");
    lbStatus->setGeometry(50, 0, 310, 40);
    lbStatus->setAlignment(Qt::AlignCenter);
    isOpen = false;

    lbScan = new CustomeQlabel("", ui->frame_3);
    lbScan->setObjectName("lbScan");
    lbScan->setGeometry(0, 0, 400, 240);
    lbScan->setAlignment(Qt::AlignCenter);

    btnPre = new QToolButton(ui->frame_3);
    btnPre->setGeometry(0,60,40,121);
    btnPre->setIcon(QIcon(":/images/images/pre.png"));
    btnPre->setStyleSheet("border-top-right-radius:34px;"
                          "border-bottom-right-radius:34px;");

    btnNext = new QToolButton(ui->frame_3);
    btnNext->setGeometry(360,60,40,121);
    btnNext->setIcon(QIcon(":/images/images/next.png"));
    btnNext->setStyleSheet("border-top-left-radius:34px;"
                           "border-bottom-left-radius:34px;");
    isScanned = false;
    txtSearch->setValidator(new QIntValidator);

    isSet = false;
    isOKDown = true;

    connect(lbScan, SIGNAL(clicked()), SLOT(viewInformation()));
    connect(timer, SIGNAL(timeout()), SLOT(checkStatus()));
    connect(ui->btnSearch, SIGNAL(clicked(bool)), SLOT(runKeyboard()));
    connect(txtSearch, SIGNAL(textChanged(QString)), SLOT(search_textChange(QString)));
    connect(btnNext,SIGNAL(clicked()),SLOT(btnNext_clicked()));
    connect(btnPre,SIGNAL(clicked()),SLOT(btnPre_clicked()));
    stopScanning();
    if(wiringPiSetup()<0)qDebug()<<"cannot setup";

    pinMode(BUTTON_OK,INPUT);
    QTimer *buttonTimer = new QTimer(this);
    connect(buttonTimer,SIGNAL(timeout()),SLOT(statusButtonOK()));
    buttonTimer->start(1000/15);

}

void S_Search::statusButtonNO(){
    if(digitalRead(BUTTON_NO) == 1) statusNORaising();
    else statusNOFalling();
}

void S_Search::statusButtonOK(){
    if(digitalRead(BUTTON_OK) == 1) statusOKRaising();
    else statusOKFalling();
}

void S_Search::statusOKFalling() {
    if(isOKDown){
        qDebug()<< "Press";
        S_Search::instance()->on_btnAdd_clicked();
        isOKDown = false;
        isEnableBt = true;
    }
}

void S_Search::statusOKRaising(){
    if(!isOKDown && isEnableBt){
        qDebug()<< "RS";
        S_Search::instance()->on_btnAdd_clicked();
        isOKDown = true;
    }
}
void S_Search::statusNOFalling() {

}

void S_Search::statusNORaising(){

}

void S_Search::btnPre_clicked(){
    qDebug() << "pre";
    if(index == 0) {
        index = listProduct.size()-1;
    } else {
        index--;
    }
    showProduct();
}

void S_Search::btnNext_clicked(){
    qDebug() << "Next";
    if(index == listProduct.size()-1) {
        index =0 ;
    } else {
        index++;
    }
    showProduct();
}

void S_Search::viewInformation()
{
    if(product)
    {
        S_Product *productScreen = S_Product::instance();

        productScreen->setModal(true);
        if(action == View || action == Shopping)
        {
            if(product)
            {
                productScreen->action = S_Product::View;
                productScreen->viewInformation(product);
                productScreen->setEnabled(false);
                productScreen->showFullScreen();
                isOpen = false;this->close();
            }
        }
        else if(action == Insert)
        {
            if(product)
            {
                qDebug() << "UPDATE";
                productScreen->action = S_Product::InsertMore;
                productScreen->viewInformation(product);
            }
            else
            {
                qDebug() << "Insert";
                productScreen->action = S_Product::Insert;
                E_Barcode *barcode = new E_Barcode();
                barcode->analysisBarcode(bc->getSymbols());
                productScreen->setBarcode(barcode);
            }
            productScreen->setEnabled(true);
            productScreen->showFullScreen();
            isOpen = false;this->close();
        }
    }
}

void S_Search::setState(Action newAction)
{
    this->action = newAction;
    isOpen = true;
    isEnableBt = false;
    stopScanning();
}

S_Search::~S_Search()
{
    delete ui;
}

void S_Search::on_btnPlus_clicked()
{
    if(isScanned)
    {
        value = value + 1;
        ui->lcdNumber->display(value);
    }
    else
    {
        number = number + 1;
        ui->lcdNumber->display(number);
    }
}



void S_Search::on_btnMinus_clicked()
{
    if(isScanned)
    {
        if(value > 1)
        {
            value = value - 1;
            ui->lcdNumber->display(value);
        }
        else
        {
            value = 1;
            ui->lcdNumber->display(value);
        }
    }
    else
    {
        if(number > 1)
        {
            number = number - 1;
            ui->lcdNumber->display(number);
        }
        else
        {
            number = 1;
            ui->lcdNumber->display(number);
        }
    }
}


void S_Search::search_textChange(const QString &value)
{
    if(isValidBarcode(value))
    {
        foreach (E_Product *item, listProduct) {
            if(value == item->barcode->barcode) {
                index = listProduct.indexOf(item);
                showProduct();
                return;
            }
        }
        searchByBarcode(value);
    }
    index = listProduct.size()-1;
    showProduct();
}

void S_Search::on_btnBack_clicked()
{
    if(isScanned)
    {
        stopScanning();
    }else if (!listProduct.isEmpty())
    {
        setBackToDefaul();
    }
    else if(action == View)
    {
        on_btnMenu_clicked();
    }
    else if(action == Shopping)
    {
        S_Checkout *checkout = S_Checkout::instance();
        checkout->setModal(true);
        checkout->showFullScreen();
        isOpen = false;this->close();
    }
    else
    {
        S_InventoryManager *inventoryScreen = S_InventoryManager::instance();
        inventoryScreen->setModal(true);
        inventoryScreen->showFullScreen();
        inventoryScreen->setDataToTable();
        isOpen = false;this->close();
    }
}

void S_Search::suppendCam()
{
    if(timer->isActive())
    {
        timer->stop();
        bc->releaseCam();
    }

    lbStatus->setStyleSheet("background-color: qlineargradient(spread:pad,"
                            " x1:0.773136, y1:0.347, x2:0.795, y2:0.0284091,"
                            " stop:0.0909091 rgba(248, 148, 3, 255), stop:0.761364"
                            " rgba(253, 169, 0, 255));");
    if(!bc->listBarcode.isEmpty()) {
        foreach (QString item, bc->listBarcode) {
            searchByBarcode(item);
        }
        bc->listBarcode.clear();
        isScanned = false;

    }
    if(!listProduct.isEmpty()) {
        showProduct();
    } else {
        setBackToDefaul();
    }
}
void S_Search::stopScanning() {
    if(timer->isActive())
    {
        timer->stop();
        bc->releaseCam();
    }

    lbStatus->setStyleSheet("background-color: qlineargradient(spread:pad,"
                            " x1:0.773136, y1:0.347, x2:0.795, y2:0.0284091,"
                            " stop:0.0909091 rgba(248, 148, 3, 255), stop:0.761364"
                            " rgba(253, 169, 0, 255));");
    if(!bc->listBarcode.isEmpty()) {
        foreach (QString item, bc->listBarcode) {
            searchByBarcode(item);
        }
        bc->listBarcode.clear();
        isScanned = false;
        ui->lbQty->setText(QString::number(listProduct.size()));
        index = listProduct.size()-1;
        showProduct();
    }else {
        setBackToDefaul();
    }
}


void S_Search::setBackToDefaul()
{
    value = 1;
    number = 1;
    index = 0;
    isScanned = false;
    listProduct.clear();
    ui->lbQty->setText(QString::number(listProduct.size()));
    btnNext->setVisible(false);
    btnPre->setVisible(false);
    ui->btnCheckout->setIcon(QIcon(":/images/images/checkout.png"));
    ui->lcdNumber->display(value);

    bc->checkCam();
    lbStatus->setText(bc->getSymbols());
    isScanned = false;
    e_barcode = NULL;
    product = NULL;
    lbScan->setPixmap(QPixmap(":/images/images/search-barcode.png"));
    ui->btnAdd->setIcon(QIcon(":/images/images/search-icon.png"));
}

void S_Search::runKeyboard()
{
    Keyboard *keyboard = Keyboard::instance();
    QLineEdit *line = txtSearch;
    line->setPlaceholderText("Enter Barcode to Search");
    keyboard->setLineEdit(txtSearch);
    keyboard->setWindowModality(Qt::WindowModal);
    keyboard->showFullScreen();
    suppendCam();
}

void S_Search::searchByBarcode(QString barcode)
{
    E_Barcode *e_barc = E_Barcode::getBarcode(barcode);

    E_Product *prd = new E_Product();
    prd->barcode = e_barc;
    if(e_barc)
    {
        prd = E_Product::getProductByID(e_barc->proID);
        if(!prd) {
            prd = new E_Product();
        }
        e_barc->barcode = barcode;
        prd->barcode = e_barc;
    } else {
        e_barc = new E_Barcode();
        e_barc->barcode = barcode;
        prd->barcode = e_barc;
    }
    bool isExist = false;
    foreach (E_Product *item, listProduct) {
        if(item->barcode->barcode == barcode) {
            isExist = true;
            break;
        }
    }
    if(!isExist)
        listProduct.append(prd);

}

void S_Search::showProduct()
{
    if(!listProduct.isEmpty()){
        product = listProduct[index];
        if(product->name.length() > 1){
            lbStatus->setText(product->name);
            if(!product->listPicture.isEmpty())
                lbScan->setPixmap(QPixmap(QDir::currentPath() + "/" + product->listPicture[0]->picUrl).scaled(lbScan->size()));
            ui->lcdNumber->display(value);
        } else {
            lbStatus->setText(product->barcode->barcode);
            lbScan->setPixmap(QPixmap(":/images/images/NotFound.png"));
        }
        if(action == View || action == Shopping)
        {
            ui->btnAdd->setIcon(QIcon(":/images/images/add.png"));
        }
        else if(action == Insert)
        {
            ui->btnAdd->setIcon(QIcon(":/images/images/AddNew.png"));
        }
        if(listProduct.size() > 1) {
            btnPre->setVisible(true);
            btnNext->setVisible(true);
        } else {
            btnPre->setVisible(false);
            btnNext->setVisible(false);
        }
    }
}

void S_Search::checkStatus()
{
    if(timer->isActive())
    {
        if(!bc->timer->isActive())
        {
            stopScanning();
        }
        else
        {
            if(isSet)
            {
                lbStatus->setText("Scanning!!!");
                lbStatus->setStyleSheet("background-color: rgb(194, 194, 194);");
            }
            else
            {
                lbStatus->setStyleSheet("");
            }
            isSet = !isSet;
            if(!bc->listBarcode.isEmpty()) {
                foreach (QString item, bc->listBarcode) {
                    searchByBarcode(item);
                }
                ui->lbQty->setText(QString::number(listProduct.size()));
                //                bc->listBarcode.clear();
            }
        }
    }
    else
    {
        //TODO: Set default picture
    }
}


void S_Search::scanBarcode()
{
    qDebug() << "set";
    bc->setSymbols("");
    bc->qty = this->number;
    bc->listBarcode.clear();
    bc->setLableScan(lbScan);
    bc->scanBarcode();
    isScanned = true;
}

bool S_Search::isValidBarcode(QString barcode)
{
    int sum = 0;
    if(barcode.length()>1){
        for(int i = 0; i < barcode.length() - 1; i++)
        {
            if(i % 2 == 0)
            {
                sum += barcode.at(i).digitValue() * 1;
            }
            else
            {
                sum += barcode.at(i).digitValue() * 3;
            }
        }
        return ((((sum / 10) + 1) * 10 - sum) == barcode.at(barcode.length() - 1).digitValue() ? true : false); //"s= " + ((sum / 10) + 1) * 10 - sum;
    }
    return false;
}

void S_Search::on_btnCheckout_clicked()
{
    //    isValidBarcode("5060214370028");
    S_Checkout *checkout = S_Checkout::instance();
    checkout->setModal(true);
    checkout->action = S_Checkout::View;
    checkout->showDataToTable();
    checkout->showFullScreen();
    stopScanning();
    isOpen = false;
    isOpen = false;this->close();
}

void S_Search::on_btnMenu_clicked()
{
    S_Menu *menu = S_Menu::instance();
    menu->setModal(true);
    menu->showFull();
    bc->releaseCam();
    bc->listBarcode.clear();
    stopScanning();
    isOpen = false;this->close();
}

void S_Search::on_btnAdd_clicked()
{
    qDebug() << "click";
    if(!listProduct.isEmpty())
    {
        if(action == View || action == Shopping)
        {
            if(product)
            {
                if(product->name.isEmpty()) {
                    QMessageBox::warning(this, "Warning", "This Product is Not Found.");
                } else
                if(ui->lcdNumber->intValue() < product->quantity)
                {
                    ShoppingCart *cart = ShoppingCart::instance();
                    cart->addCart(product, ui->lcdNumber->intValue());
                    qDebug() << "add cart";
                    if(listProduct.size() == 1) {
                        setBackToDefaul();
                    } else  {
                        btnPre_clicked();
                        if(index == listProduct.size())            {
                            listProduct.removeAt(0);
                        } else {
                            listProduct.removeAt(index + 1);
                        }
                    }
                }
                else
                {
                    QMessageBox::warning(this, "Warning", "Not enough items for sale. Max: " + QString::number(product->quantity));
                }
            }
        }
        else
        {
            viewInformation();
        }
    }
    else
    {
        if(!timer->isActive())
        {
            scanBarcode();
            timer->start(500);
        }
        else
        {
            suppendCam();
        }
    }
}

void S_Search::on_btnSearch_clicked()
{
    txtSearch->setText("");
}
