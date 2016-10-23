#ifndef S_INVENTORYMANAGER_H
#define S_INVENTORYMANAGER_H

#include <QDialog>

namespace Ui {
class S_InventoryManager;
}

class S_InventoryManager : public QDialog
{
    Q_OBJECT

public:
    explicit S_InventoryManager(QWidget *parent = 0);
    ~S_InventoryManager();

private:
    Ui::S_InventoryManager *ui;
};

#endif // S_INVENTORYMANAGER_H
