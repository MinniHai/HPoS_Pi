#ifndef S_INVENTORYMANAGER_H
#define S_INVENTORYMANAGER_H

#include <QDialog>
#include <QList>
#include <QTableWidget>
#include <QTableWidgetItem>

class E_Product;
namespace Ui {
    class S_InventoryManager;
}

class S_InventoryManager : public QDialog
{
    Q_OBJECT

public:
    static S_InventoryManager *s_instance;
    static S_InventoryManager *instance();

    explicit S_InventoryManager(QWidget *parent = 0);
    ~S_InventoryManager();
    QList<E_Product *> listProduct;
    void setDataToTable();
    QTableWidgetItem *createTableWidgetItem(const QString &text) const;

private slots:

    void searchInventory(QString text);

    void on_btnMenu_clicked();

    void runKeyboard();

    void on_btnBack_clicked();

    void on_btnNew_clicked();
    void edit_clicked(int row);

private:

    void resizeEvent(QResizeEvent *);
    Ui::S_InventoryManager *ui;
};

#endif // S_INVENTORYMANAGER_H
