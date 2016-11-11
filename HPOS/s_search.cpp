#include "s_search.h"
#include "s_menu.h"

#include <QString>
#include <QIcon>
#include "e_barcode.h"
#include "e_product.h"
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

using namespace std;
E_Barcode *e_barcode;

S_Search *S_Search::s_instance;



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
    lbStatus->setGeometry(50, 0, 351, 41);
    lbStatus->setAlignment(Qt::AlignCenter);

    lbScan = new CustomeQlabel("", ui->frame_3);
    lbScan->setObjectName("lbScan");
    lbScan->setGeometry(0, 0, 400, 240);
    lbScan->setAlignment(Qt::AlignCenter);

    isScanned = false;
    value = 1 ;
    txtSearch->setValidator(new QIntValidator);

    number = 1;
    isSet = false;

    connect(lbScan, SIGNAL(clicked()), SLOT(viewInformation()));
    connect(timer, SIGNAL(timeout()), SLOT(checkStatus()));
    connect(ui->btnSearch, SIGNAL(clicked(bool)), SLOT(runKeyboard()));
    connect(txtSearch, SIGNAL(textChanged(QString)), SLOT(search_textChange(QString)));
    setBackToDefaul();
}

void S_Search::viewInformation()
{
    if(isScanned)
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
                this->close();
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
            this->close();
        }
    }
}

void S_Search::setState(Action newAction)
{
    this->action = newAction;
    setBackToDefaul();
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
    //    lbStatus->setText(value);
    if(isValidBarcode(value))
    {
        isScanned = searchByBarcode(value);
        if(action == View || action == Shopping)
        {
            if(isScanned)
            {
                ui->btnAdd->setIcon(QIcon(":/images/images/add.png"));
            }
        }
        else if(action == Insert)
        {

            ui->btnAdd->setIcon(QIcon(":/images/images/AddNew.png"));
        }
    } else {
        lbStatus->setText(value);
        lbScan->setPixmap(QPixmap(":/images/images/NotFound.png"));
    }
}

void S_Search::on_btnBack_clicked()
{
    if(isScanned)
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
        this->close();
    }
    else
    {
        S_InventoryManager *inventoryScreen = S_InventoryManager::instance();
        inventoryScreen->setModal(true);
        inventoryScreen->showFullScreen();
        inventoryScreen->setDataToTable();
        this->close();
    }
}


void S_Search::setBackToDefaul()
{
    value = 1;
    number = 1;
//    txtSearch->setText("");
    ui->lcdNumber->display(value);
    lbStatus->setStyleSheet("background-color: qlineargradient(spread:pad,"
                            " x1:0.773136, y1:0.347, x2:0.795, y2:0.0284091,"
                            " stop:0.0909091 rgba(248, 148, 3, 255), stop:0.761364"
                            " rgba(253, 169, 0, 255));");
    if(timer->isActive())
    {
        timer->stop();
        bc->releaseCam();
    }
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
    keyboard->show();
    setBackToDefaul();
}

bool S_Search::searchByBarcode(QString barcode)
{
    qDebug() << barcode;
    e_barcode = E_Barcode::getBarcode(barcode);
    if(e_barcode)
    {
        product = E_Product::getProductByID(e_barcode->proID);
        if(product)
        {
            lbStatus->setText(product->name);
            ui->lcdNumber->display(1);
            return true;
        }
    }
    else
    {
        lbStatus->setText(barcode);
        lbScan->setPixmap(QPixmap(":/images/images/NotFound.png"));

    }
    return false;
}

void S_Search::checkStatus()
{
    if(timer->isActive())
    {
        if(bc->getSymbols().length() > 1)
        {
            if(isValidBarcode(bc->getSymbols()))
            {
                timer->stop();
                lbStatus->setStyleSheet("background-color: qlineargradient(spread:pad,"
                                        " x1:0.773136, y1:0.347, x2:0.795, y2:0.0284091,"
                                        " stop:0.0909091 rgba(248, 148, 3, 255), stop:0.761364"
                                        " rgba(253, 169, 0, 255));");
                isScanned = searchByBarcode(bc->getSymbols());
                if(action == View || action == Shopping)
                {
                    if(isScanned)
                    {
                        ui->btnAdd->setIcon(QIcon(":/images/images/add.png"));
                    }
                }
                else if(action == Insert)
                {
                    isScanned = true;
                    ui->btnAdd->setIcon(QIcon(":/images/images/AddNew.png"));
                }
            }
            else
            {
                scanBarcode();
            }

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
    bc->setLableScan(lbScan);
    bc->scanBarcode();
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
    this->close();
}

void S_Search::on_btnMenu_clicked()
{
    S_Menu *menu = S_Menu::instance();
    menu->setModal(true);
    menu->showFull();
    setBackToDefaul();
    this->close();
}

void S_Search::on_btnAdd_clicked()
{
    if(isScanned)
    {
        if(action == View || action == Shopping)
        {
            if(product)
            {
                if(ui->lcdNumber->intValue() < product->quantity)
                {
                    ShoppingCart *cart = ShoppingCart::instance();
                    cart->addCart(product, ui->lcdNumber->intValue());
                    qDebug() << "add cart";
                    setBackToDefaul();
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
            qDebug() << "timer not Active";
        }
    }
}

void S_Search::on_btnSearch_clicked()
{
    txtSearch->setText("");
}
