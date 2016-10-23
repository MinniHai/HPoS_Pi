#include "s_checkout.h"
#include "ui_checkoutScreen.h"
#include "QStandardItemModel"
#include "s_menu.h"
#include "s_search.h"
#include "s_payment.h"
#include "shoppingcart.h"
#include "e_product.h"

#include <QHeaderView>
#include <QTableWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMainWindow>
#include <QResizeEvent>


S_Checkout *S_Checkout::s_instance;
S_Checkout *S_Checkout::instance()
{
    if(!s_instance)
    {
        s_instance = new S_Checkout();
    }
    return s_instance;
}

S_Checkout::S_Checkout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Checkout)
{
    ui->setupUi(this);
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    ShoppingCart *cart = ShoppingCart::instance();
    if(!cart->cart.isEmpty())
    {
        QList<E_Product *> productList = (QList<E_Product *>)cart->cart.keys();
        QList<int> quantity = cart->cart.values();
        for(int i = 0 ; i < productList.size(); i++)
        {
            ui->tableWidget->insertRow(i);
            ui->tableWidget->setItem(i, 0, createTableWidgetItem(productList[i]->name));
            ui->tableWidget->setItem(i, 1, createTableWidgetItem(QString::number(quantity[i])));
            ui->tableWidget->setItem(i, 2, createTableWidgetItem(QString::number(productList[i]->price)));
            ui->tableWidget->setItem(i, 3, createTableWidgetItem(QString::number(quantity[i] * productList[i]->price)));
            QWidget *pWidget = new QWidget();
            QPushButton *btn_edit = new QPushButton();
            btn_edit->setText("Edit");
            btn_edit->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
            //        btn_edit->setStyleSheet("background-color:black");
            QHBoxLayout *pLayout = new QHBoxLayout(pWidget);
            pLayout->addWidget(btn_edit);
            pLayout->setAlignment(Qt::AlignHCenter);
            pLayout->setContentsMargins(0, 0, 0, 0);
            pWidget->setLayout(pLayout);
            ui->tableWidget->setCellWidget(i, 4, pWidget);
        }
    }
}

QTableWidgetItem *S_Checkout::createTableWidgetItem(const QString &text) const
{
    QTableWidgetItem *item = new QTableWidgetItem(text);
    item->setTextAlignment(Qt::AlignCenter);
    return item;
}

S_Checkout::~S_Checkout()
{
    delete ui;
}


void S_Checkout::resizeEvent(QResizeEvent *event)
{
    int width =  event->size().width();
    ui->tableWidget->setColumnWidth(0, width * 7 / 16);
    ui->tableWidget->setColumnWidth(1, width * 2 / 16);
    ui->tableWidget->setColumnWidth(2, width * 3 / 16);
    ui->tableWidget->setColumnWidth(3, width * 3 / 16);
    ui->tableWidget->setColumnWidth(4, width * 0.95 / 16);

}




void S_Checkout::on_btnBack_clicked()
{

    S_Menu menu;
    menu.setModal(true);
    //menu.showFullScreen();
    menu.exec();
    this->close();

}

void S_Checkout::on_btnAdd_clicked()
{
    S_Search *search = S_Search::instance();
    search->setModal(true);
    search->showFullScreen();
    search->exec();
    this->close();

}

void S_Checkout::on_btnCheckOK_clicked()
{
    S_Payment payment;
    payment.setModal(true);
    //payment.showFullScreen();
    payment.exec();
    this->close();

}
