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
#include <QFont>

S_InventoryManager *S_InventoryManager::s_instance;


S_InventoryManager *S_InventoryManager::instance()
{
    if(!s_instance)
    {
        s_instance = new S_InventoryManager();
    }
    return s_instance;
}

S_InventoryManager::S_InventoryManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::S_InventoryManager)
{
    ui->setupUi(this);
    ui->cbbSearchType->addItem("Name", QVariant("proName"));
    ui->cbbSearchType->addItem("Barcode", QVariant(""));
    ui->cbbSearchType->addItem("Category", QVariant("ctID"));
    ui->cbbSearchType->addItem("Manufacturer", QVariant(""));

    ui->tblListInventory->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->tblListInventory->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->cbbSearchType->setCurrentIndex(ui->cbbSearchType->findText("Name"));

    ledSearch = new CustomeLineEdit(ui->frame_3);
    ledSearch->setGeometry(60,0,301,41);
    ledSearch->setObjectName("ledSearch");
    QFont font("times",50,QFont::Normal,true);
    ledSearch->setFont(font);
    ledSearch->setPlaceholderText("Search...");
    ledSearch->setClearButtonEnabled(true);

    ui->btnDelete->setEnabled(false);
    connect(ledSearch, SIGNAL(textChanged(QString)), SLOT(searchInventory(QString)));

    listProduct.clear();
    listProduct = E_Product::getAllProduct();
}


S_InventoryManager::~S_InventoryManager()
{
    delete ui;
}

void S_InventoryManager::on_btnMenu_clicked()
{
    S_Menu *menu = S_Menu::instance();
    menu->setModal(true);
    menu->showFull();
    menu->showFullScreen();
    this->close();
}

void S_InventoryManager::resizeEvent(QResizeEvent *)
{
    int width =  480;
    ui->tblListInventory->setColumnWidth(0, width * 5.5 / 19);
    ui->tblListInventory->setColumnWidth(1, width * 3 / 19);
    ui->tblListInventory->setColumnWidth(2, width * 3 / 19);
    ui->tblListInventory->setColumnWidth(3, width * 2 / 19);
    ui->tblListInventory->setColumnWidth(4, width * 4 / 19);
    ui->tblListInventory->setColumnWidth(5, width * 1.45 / 19);

}

void S_InventoryManager::on_btnBack_clicked()
{
    S_Menu *menu = S_Menu::instance();
    menu->setModal(true);
    menu->showFull();
    this->close();
}

void S_InventoryManager::setDataToTable()
{
    ui->tblListInventory->clearContents();
    ui->tblListInventory->setRowCount(0);

    if(!listProduct.isEmpty())
    {
        QSignalMapper *mapper = new QSignalMapper(this);
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
            pWidget->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
            ui->tblListInventory->setCellWidget(i, 5, pWidget);
            mapper->setMapping(btn_edit, i);
            connect(btn_edit, SIGNAL(clicked(bool)), mapper, SLOT(map()));
        }
        connect(mapper, SIGNAL(mapped(int)), this, SLOT(edit_clicked(int)));
    }
    ui->btnBack->setFocus();
}

void S_InventoryManager::edit_clicked(int row)
{
    S_Product *productScreen = S_Product::instance();
    productScreen->action = S_Product::Update;
    E_Product *product = listProduct.at(row);
    productScreen->viewInformation(product);
    productScreen->setEnabled(true);
    productScreen->showFullScreen();
    this->close();
}

QTableWidgetItem *S_InventoryManager::createTableWidgetItem(const QString &text) const
{
    QTableWidgetItem *item = new QTableWidgetItem(text);
    item->setTextAlignment(Qt::AlignCenter);
    return item;
}


void S_InventoryManager::on_btnNew_clicked()
{
    //    S_Product *product = S_Product::instance();
    //    product->setModal(true);
    //    product->showFullScreen();
    //    this->close();
    S_Search *searchScreen = S_Search::instance();
    searchScreen->setModal(true);
    searchScreen->showFullScreen();
    searchScreen->setState(S_Search::Insert);
    this->close();
}

void S_InventoryManager::runKeyboard()
{
    Keyboard *keyboard = Keyboard::instance();
    QLineEdit *line = ledSearch;
    keyboard->setLineEdit(line);
    keyboard->setWindowModality(Qt::WindowModal);
    keyboard->showFullScreen();
}

void S_InventoryManager::searchInventory(QString text)
{
    listProduct.clear();
    if(ui->cbbSearchType->currentText() == "Name")
    {

        listProduct = E_Product::searchByColumn(ui->cbbSearchType->currentData().toString()
                                                , text);

    }
    else if(ui->cbbSearchType->currentText() == "Category")
    {
        QList<E_Category *> listCategory = E_Category::searchCategoryByName(text);
        foreach(E_Category *item, listCategory)
        {
            foreach(E_Product *pro, E_Product::getProductByColumn(
                        ui->cbbSearchType->currentData().toString()
                        , item->ctID))
            {
                if(!listProduct.contains(pro))
                {
                    listProduct.append(pro);
                }
            }
        }
    }
    else if(ui->cbbSearchType->currentText() == "Barcode")
    {
        foreach(E_Barcode *item, E_Barcode::searchBarcode(text))
        {
            E_Product *pro = E_Product::getProductByID(item->proID);
            if(!listProduct.contains(pro))
            {
                listProduct.append(pro);
            }

        }
    }
    else if(ui->cbbSearchType->currentText() == "Manufacturer")
    {
        foreach(E_Manufacturer *manuItem,  E_Manufacturer::searchByName(text))
        {

            foreach(E_Barcode *item, E_Barcode::getBarcodeByManuRefix(manuItem->manuPrefix))
            {
                E_Product *pro = E_Product::getProductByID(item->proID);
                if(!listProduct.contains(pro))
                {
                    listProduct.append(pro);
                    qDebug() << "append";
                }
            }
        }
    }
    setDataToTable();
}
