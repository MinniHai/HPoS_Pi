#include "s_checkout.h"
#include "ui_checkoutScreen.h"
#include "QStandardItemModel"
#include "s_menu.h"
#include "s_search.h"
#include "s_payment.h"
#include "s_product.h"
#include "shoppingcart.h"
#include "e_product.h"

#include <QHeaderView>
#include <QTableWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QMainWindow>
#include <QSignalMapper>


S_Checkout *S_Checkout::s_instance;
S_Checkout *S_Checkout::instance()
{
    if(!s_instance)
    {
        s_instance = new S_Checkout();
        qDebug() << "new Checkout";
    }
    return s_instance;
}

S_Checkout::S_Checkout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Checkout)
{
    ui->setupUi(this);
    ui->tableWidget->verticalHeader()->hide();
    ui->tableWidget->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

}

void S_Checkout::showDataToTable()
{
    //reset tableview
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    ShoppingCart *cart = ShoppingCart::instance();
    ui->lblCash->setText(QString::number(cart->subTotal));
    if(!cart->cart.isEmpty())
    {
        //get cart in shopping cart
        QList<E_Product *> productList = cart->cart;
        QList<int> quantity = cart->quantity;
        //set newer data to tableview
        QSignalMapper *mapper = new QSignalMapper(this);
        for(int i = 0 ; i < productList.size(); i++)
        {
            ui->tableWidget->insertRow(i);
            ui->tableWidget->setItem(i, 0, createTableWidgetItem(productList[i]->name));
            ui->tableWidget->setItem(i, 1, createTableWidgetItem(QString::number(quantity[i])));
            ui->tableWidget->setItem(i, 2, createTableWidgetItem(QString::number(productList[i]->price)));
            ui->tableWidget->setItem(i, 3, createTableWidgetItem(QString::number(quantity[i] * productList[i]->price)));

            //add button to table
            QWidget *pWidget = new QWidget();
            QPushButton *btn_edit = new QPushButton();
            btn_edit->setText("-");
            btn_edit->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
            QHBoxLayout *pLayout = new QHBoxLayout(pWidget);
            pLayout->addWidget(btn_edit);
            pLayout->setAlignment(Qt::AlignHCenter);
            pLayout->setContentsMargins(0, 0, 0, 0);
            pWidget->setLayout(pLayout);
            ui->tableWidget->setCellWidget(i, 4, pWidget);
            mapper->setMapping(btn_edit, i);
            connect(btn_edit, SIGNAL(clicked(bool)), mapper, SLOT(map()));
        }
        connect(mapper, SIGNAL(mapped(int)), this, SLOT(edit_clicked(int)));
        connect(ui->tableWidget, SIGNAL(cellClicked(int, int)), SLOT(cell_click(int, int)));
    }
}

void S_Checkout::edit_clicked(int row)
{
    ShoppingCart::instance()->removeCart(ShoppingCart::instance()->cart[row]);
    showDataToTable();
}

void S_Checkout::cell_click(int row, int column)
{
    qDebug() << QString::number(row) + " : " + QString::number(column);
    S_Product *productScreen = S_Product::instance();

    productScreen->setModal(true);
    productScreen->action = S_Product::UpdateCart;
    productScreen->setEnabled(false);
    productScreen->viewInformation(ShoppingCart::instance()->cart[row]);
    productScreen->setQuantityText(ShoppingCart::instance()->quantity[row]);
    productScreen->showFullScreen();
    this->close();
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

    if(action == Shopping)
    {
        on_btnMenu_clicked();
    }
    else if(action == View)
    {
        S_Search *search = S_Search::instance();
        search->setModal(true);
        search->setBackToDefaul();
        search->showFullScreen();
        this->close();
    }

}

void S_Checkout::on_btnAdd_clicked()
{
    S_Search *search = S_Search::instance();
    search->setModal(true);
    search->action  = S_Search::Shopping;
    search->showFullScreen();
    this->close();

}

void S_Checkout::on_btnCheckOK_clicked()
{
    S_Payment *payment = S_Payment::instance();
    payment->setModal(true);
    payment->fillData();
    payment->showFullScreen();
    this->close();

}

void S_Checkout::on_btnMenu_clicked()
{
    S_Menu *menu = S_Menu::instance();
    menu->setModal(true);
    menu->showFull();
    //    menu.exec();
    this->close();
}

void S_Checkout::on_btnSearch_clicked()
{
    ShoppingCart::instance()->cancelCart();
    showDataToTable();
}
