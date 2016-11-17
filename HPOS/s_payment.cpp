#include "s_payment.h"
#include "ui_paymentScreen.h"
#include "s_checkout.h"
#include "s_menu.h"
#include "shoppingcart.h"
#include <QMessageBox>
#include <qtrpt.h>
#include <QtPrintSupport/QPrinter>
#include <QPrinterInfo>

S_Payment::S_Payment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Payment)
{
    ui->setupUi(this);
    connect(ui->ledPayment, SIGNAL(textChanged(QString)), SLOT(calculate()));
}

S_Payment *S_Payment::s_instance;
S_Payment *S_Payment::instance()
{
    if(!s_instance)
    {
        s_instance = new S_Payment();
    }
    return s_instance;
}

S_Payment::~S_Payment()
{
    delete ui;
}

QString S_Payment::getCash(){
    return ui->ledPayment->text();
}

QString S_Payment::getExchange(){
    return ui->ledBalance->text();
}

void S_Payment::calculate()
{
    double balance = ui->ledPayment->text().toDouble() - ShoppingCart::instance()->subTotal;
    ui->ledBalance->setText(QString::number(balance));
}

void S_Payment::fillData()
{
    ui->lblCash_3->setText(QString::number(ShoppingCart::instance()->subTotal));
}

void S_Payment::on_btnBack_clicked()
{
    S_Checkout *check = S_Checkout::instance();
    check->setModal(true);
    check->showFullScreen();
    this->close();
}



void S_Payment::on_btnCheckOK_clicked()
{
    if(ui->ledPayment->text().toDouble() - ShoppingCart::instance()->subTotal >= 0)
    {
        if(ShoppingCart::instance()->saveCarts())
        {
            ShoppingCart::instance()->cancelCart();
            QMessageBox::information(this, "Payment", "Done");
        }
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Not Enought Money for Cash");
    }
}

void S_Payment::on_btnPrint_clicked()
{
    S_Checkout::instance()->print();
    QMessageBox::information(this, "Payment", "Done");
}

void S_Payment::on_btnMenu_clicked()
{
    S_Menu *menu = S_Menu::instance();
    menu->setModal(true);
    menu->showFull();
    this->close();
}
