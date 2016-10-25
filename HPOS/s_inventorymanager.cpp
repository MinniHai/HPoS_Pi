#include "s_inventorymanager.h"
#include "ui_s_inventorymanager.h"
#include "s_menu.h"
#include "s_search.h"
#include "s_product.h"
#include "e_category.h"
#include "e_manufacturer.h"
#include "e_product.h"
#include "keyboard.h"
#include "e_barcode.h"

#include "QResizeEvent"
#include <QPushButton>
#include <QHBoxLayout>
#include <QDebug>
#include <QVariant>

S_InventoryManager::S_InventoryManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::S_InventoryManager)
{
    ui->setupUi(this);
    listProduct = E_Product::getAllProduct();
    ui->cbbSearchType->addItem("Name", QVariant("proName"));
    ui->cbbSearchType->addItem("Barcode", QVariant(""));
    ui->cbbSearchType->addItem("Category", QVariant(""));
    ui->cbbSearchType->addItem("Manufacturer", QVariant(""));

    connect(ui->ledSearch, SIGNAL(selectionChanged()), SLOT(runKeyboard()));
    connect(ui->ledSearch,SIGNAL(textChanged(QString)),SLOT(searchInventory()));
   // connect(ui->ledSearch,SIGNAL(textChanged(QString)),SLOT(searchByBarcode()));

}


S_InventoryManager::~S_InventoryManager()
{
    delete ui;
}

void S_InventoryManager::on_btnMenu_3_clicked()
{
    S_Menu menu;
    menu.setModal(true);
    menu.showFullScreen();
    menu.exec();
    this->hide();
}

void S_InventoryManager::resizeEvent(QResizeEvent *event)
{
    int width =  480;
    ui->tblListInventory->setColumnWidth(0, width * 5.5 / 19);
    ui->tblListInventory->setColumnWidth(1, width * 3 / 19);
    ui->tblListInventory->setColumnWidth(2, width * 3 / 19);
    ui->tblListInventory->setColumnWidth(3, width * 2 / 19);
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

void S_InventoryManager::setDataToTable()
{
    ui->tblListInventory->clearContents();
    ui->tblListInventory->setRowCount(0);

    if(!listProduct.isEmpty())
    {
        for(int i = 0; i < listProduct.size(); i++)
        {
            ui->tblListInventory->insertRow(i);
            ui->tblListInventory->setItem(i, 0, createTableWidgetItem(listProduct[i]->name));
            ui->tblListInventory->setItem(i, 1, createTableWidgetItem(QString::number(listProduct[i]->price)));
            ui->tblListInventory->setItem(i, 2, createTableWidgetItem(listProduct[i]->category->categoryName));
            ui->tblListInventory->setItem(i, 3, createTableWidgetItem(QString::number(listProduct[i]->quantity)));
            ui->tblListInventory->setItem(i, 4, createTableWidgetItem(listProduct[i]->barcode->manufacturer->manuName));
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
    S_Product product;
    product.setModal(true);
    product.showFullScreen();
    product.exec();
    this->hide();
}

void S_InventoryManager::runKeyboard()
{
    Keyboard *keyboard = Keyboard::instance();
    QLineEdit *line = ui->ledSearch;
    keyboard->setLineEdit(line);
    keyboard->setWindowModality(Qt::WindowModal);
    keyboard->showFullScreen();
}

void S_InventoryManager::searchInventory()
{

    if (ui->cbbSearchType->currentText() == "Name") {

        listProduct = E_Product::searchByColumn(ui->cbbSearchType->currentData().toString()
                                                ,ui->ledSearch->text());

    } else if (ui->cbbSearchType->currentText() == "Category"){
        listProduct.clear();
        QList<E_Category *> listCategory = E_Category::searchCategoryByName(ui->ledSearch->text());
        foreach (E_Category *item, listCategory) {
            listProduct.append(E_Product::searchByColumn(ui->cbbSearchType->currentData().toString()
                                                         ,item->ctID));
        }
    }

    setDataToTable();

}

//void S_InventoryManager::searchByBarcode()
//{
//    listProduct = E_Product::searchByName(ui->ledSearch->text());
//    setDataToTable();
//}
