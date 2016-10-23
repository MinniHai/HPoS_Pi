#include "s_payment.h"
#include "ui_paymentScreen.h"
#include "s_checkout.h"
#include "s_menu.h"

S_Payment::S_Payment(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Payment)
{
    ui->setupUi(this);
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

void S_Payment::on_btnBack_clicked()
{
    S_Checkout back;
    back.setModal(true);
    back.showFullScreen();
    back.exec();
    this->close();
}

void S_Payment::on_btnCheckOK_clicked()
{
    S_Menu menu;
    menu.setModal(true);
    menu.showFullScreen();
    menu.exec();
    this->close();
}
