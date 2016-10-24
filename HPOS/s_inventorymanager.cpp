#include "s_inventorymanager.h"
#include "ui_s_inventorymanager.h"
#include "s_menu.h"
#include "s_search.h"
#include "e_category.h"
#include "e_manufacturer.h"
#include "e_product.h"
#include "QResizeEvent"
#include <QPushButton>
#include <QHBoxLayout>
#include <QDebug>

S_InventoryManager::S_InventoryManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::S_InventoryManager)
{
    ui->setupUi(this);
}

S_InventoryManager::~S_InventoryManager()
{
    delete ui;
}

void S_InventoryManager::on_btnMenu_3_clicked()
{
    S_Menu menu;
    menu.setModal(true);
    menu.exec();
    this->hide();
}

void S_InventoryManager::resizeEvent(QResizeEvent *event)
{
    int width =  480;
    ui->tblListInventory->setColumnWidth(0, width * 5.5 / 19);
    ui->tblListInventory->setColumnWidth(1, width * 3 / 19);
    ui->tblListInventory->setColumnWidth(2, width * 3 / 19);
    ui->tblListInventory->setColumnWidth(3, width * 2/ 19);
    ui->tblListInventory->setColumnWidth(4, width * 4 / 19);
    ui->tblListInventory->setColumnWidth(5, width * 1.45 / 19);

}

void S_InventoryManager::on_btnBack_3_clicked()
{
    S_Menu menu;
    menu.setModal(true);
    //menu.showFullScreen();
    menu.exec();
    this->close();
}

void S_InventoryManager::showScreen()
{
    E_Product * product= new E_Product();
    listProduct = product->getAllProduct();
            if(!listProduct.isEmpty())
                {
                    for(int i = 0; i < listProduct.size(); i++)
                    {
                        ui->tblListInventory->insertRow(i);
                        ui->tblListInventory->setItem(i, 0, createTableWidgetItem(listProduct[i]->name));
                        ui->tblListInventory->setItem(i, 1, createTableWidgetItem(QString::number(listProduct[i]->price)));
                        ui->tblListInventory->setItem(i, 2, createTableWidgetItem(QString::number(listProduct[i]->quantity)));
                        //
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
                        ui->tblListInventory->setCellWidget(i, 5, pWidget);
                    }
                }
  this->showFullScreen();
}

QTableWidgetItem *S_InventoryManager::createTableWidgetItem(const QString &text) const
{
    QTableWidgetItem *item = new QTableWidgetItem(text);
    item->setTextAlignment(Qt::AlignCenter);
    return item;
}


void S_InventoryManager::on_btnNew_clicked()
{

}
