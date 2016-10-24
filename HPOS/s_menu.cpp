#include "s_menu.h"
#include "s_search.h"
#include "s_checkout.h"
#include "e_user.h"
#include "session.h"
#include "s_usermanager.h"
#include "s_inventorymanager.h"

S_Menu *S_Menu::s_instance;
S_Menu *S_Menu::instance()
{
    if(!s_instance)
    {
        s_instance = new S_Menu();
    }
    return s_instance;
}



S_Menu::S_Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(getTimer()));
    timer->start();
}


S_Menu::~S_Menu()
{
    delete ui;
}

void S_Menu::showFull()
{
    if(Session::instance()->getUserSession())
    {
        ui->lblUser->setText(Session::instance()->getUserSession()->getUserName());
        qDebug() << Session::instance()->getUserSession()->getUserName();
    }
    else
    {
        ui->lblUser->setText("None");
    }
    this->showFullScreen();
}


void S_Menu::on_btnLogout_clicked()
{
    close();

}
void S_Menu::getTimer()
{
    QTime time = QTime::currentTime();
    QString txtTimes = time.toString("hh : mm");
    ui->lblTimer->setText(txtTimes);
}

void S_Menu::on_btnOrder_clicked()
{
    S_Search *search = S_Search::instance();
    search->setModal(true);
    search->checkStatus();
    search->showFullScreen();
    this->close();
}

void S_Menu::on_btnHumanResource_clicked()
{
    this->close();
    S_UserManager *user = new S_UserManager();
    user->setModal(true);
    user->showScreen();
    //    user->exec();


}

void S_Menu::on_btnCheckout_clicked()
{
    S_Checkout *checkout = S_Checkout::instance();
    checkout->setModal(true);
    checkout->showDataToTable();
    checkout->showFullScreen();
    this->close();
}

void S_Menu::on_btnManual_clicked()
{
    this->hide();
    S_InventoryManager inventory;
    inventory.setModal(true);
    inventory.showScreen();
    inventory.exec();
}
