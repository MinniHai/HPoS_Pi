#include "s_inventorymanager.h"
#include "ui_s_inventorymanager.h"

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
