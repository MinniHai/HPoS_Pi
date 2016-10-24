#include "s_search.h"
#include "s_menu.h"

#include <QString>
#include <string>
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
#include "customeqlabel.h"


S_Search *S_Search::s_instance;

E_Barcode *e_barcode;

using namespace std;

S_Search *S_Search::instance()
{
    if (!s_instance)
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
    //bc = new BarcodeScanner();
    txtSearch = new QLineEdit();
    timer = new QTimer(this);
    lbStatus = new CustomeQlabel("", ui->frame_2);
    lbStatus->setObjectName("lbStatus");
    lbStatus->setGeometry(50, 0, 351, 41);
    lbStatus->setAlignment(Qt::AlignCenter);

    lbScan = new CustomeQlabel("", ui->frame_3);
    lbScan->setObjectName("lbScan");
    lbScan->setGeometry(0, 0, 400, 240);

    value = 0 ;

    number = 1;
    isSet = false;
    ui->lcdNumber->display(number);

    connect(lbScan, SIGNAL(clicked()), SLOT(viewInfomation()));
    connect(timer, SIGNAL(timeout()), SLOT(checkStatus()));
    connect(ui->btnSearch, SIGNAL(clicked(bool)), SLOT(runKeyboard()));
    connect(txtSearch, SIGNAL(textChanged(QString)), SLOT(search_textChange(QString)));
    setBackToDefaul();
}

void S_Search::viewInfomation()
{
    if (e_barcode != NULL)
    {
        S_Product *product = S_Product::instance();
        product->setModal(true);
        product->showFullScreen();
        this->close();
    }
}

S_Search::~S_Search()
{
    delete ui;
}

void S_Search::on_btnPlus_clicked()
{
    number = value + 1;
    ui->lcdNumber->display(number);
    value = number;

}



void S_Search::on_btnMinus_clicked()
{
    if (number >= 1)
    {
        number = value - 1;
        ui->lcdNumber->display(number);

    }
    else
    {
        number = 0;
        ui->lcdNumber->display(number);
    }
    value = number;


}


void S_Search::search_textChange(const QString &value)
{
    //    lbStatus->setText(value);
    searchByBarcode(value);
}

void S_Search::on_btnBack_clicked()
{
}


void S_Search::setBackToDefaul()
{
    lbStatus->setStyleSheet("background-color: qlineargradient(spread:pad,"
                            " x1:0.773136, y1:0.347, x2:0.795, y2:0.0284091,"
                            " stop:0.0909091 rgba(248, 148, 3, 255), stop:0.761364"
                            " rgba(253, 169, 0, 255));");
    if (timer->isActive())
    {
        timer->stop();
        //bc->releaseCam();
    }
    //bc->checkCam();
    //lbStatus->setText(bc->getSymbols());

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

void S_Search::searchByBarcode(QString barcode)
{
    qDebug() << "barcode : " + barcode;
    QString countryPrefix = barcode.left(3);
    QString manufacturerPrefix = barcode.mid(3, 4);
    QString productPrefix = barcode.mid(7, 5);
    QString checkDigit = barcode.right(1);
    e_barcode = E_Barcode::getBarcode(countryPrefix, manufacturerPrefix, productPrefix);
    if (e_barcode)
    {
        e_barcode->checkDigit = checkDigit.toInt();
        lbStatus->setText(e_barcode->product->name);
    }
    else
    {
        lbStatus->setText("not Fount");
    }

    qDebug() << "Prefix :" + countryPrefix + "manu :" + manufacturerPrefix +
             "pro :" + productPrefix + "check : " + checkDigit;
}

void S_Search::checkStatus()
{
    if (timer->isActive())
    {
        //        if(bc->getSymbols().length() > 1)
        //        {
        //            qDebug() << "barcode : ";
        timer->stop();
        lbStatus->setStyleSheet("background-color: qlineargradient(spread:pad,"
                                " x1:0.773136, y1:0.347, x2:0.795, y2:0.0284091,"
                                " stop:0.0909091 rgba(248, 148, 3, 255), stop:0.761364"
                                " rgba(253, 169, 0, 255));");
        searchByBarcode("5060214370028");

        //        }
        //        else
        //        {
        //            if(isSet)
        //            {
        //                lbStatus->setText("Scanning!!!");
        //                lbStatus->setStyleSheet("background-color: rgb(194, 194, 194);");
        //            }
        //            else
        //            {
        //                lbStatus->setStyleSheet("");
        //            }
        //            isSet = !isSet;
        //        }
    }
    else
    {

        //TODO: Set default picture
    }
}


bool S_Search::isValidBarcode(QString barcode)
{
    int sum = 0;

    for (int i = 0; i < barcode.length() - 1; i++)
    {
        if (i % 2 == 0)
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

void S_Search::on_btnCheckout_clicked()
{
    //    isValidBarcode("5060214370028");
    if (!timer->isActive())
    {
        qDebug() << "set";
        //        bc->setSymbols("");
        //        bc->setLableScan(lbScan);
        //        bc->scanBarcode();
        timer->start(500);
    }

    //    S_Checkout *Checkout = S_Checkout::instance();;
    //    Checkout->setModal(true);
    //    Checkout->showFullScreen();
    //    this->close();
    //    Checkout->exec();
}

void S_Search::on_btnMenu_clicked()
{
    S_Menu *menu = S_Menu::instance();
    menu->setModal(true);
    menu->showFullScreen();
    setBackToDefaul();
    this->close();
    menu->exec();
}

void S_Search::on_btnAdd_clicked()
{
    if (e_barcode != NULL)
    {
        ShoppingCart *cart = ShoppingCart::instance();
        cart->addCart(e_barcode->product, 1);
        qDebug() << "add cart";
    }
}
