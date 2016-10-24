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
    explicit S_InventoryManager(QWidget *parent = 0);
    ~S_InventoryManager();
    QList<E_Product *> listProduct;
    void showScreen();
    //void resizeEvent(QResizeEvent *event);
    QTableWidgetItem *createTableWidgetItem(const QString &text) const;

private slots:
    void on_btnMenu_3_clicked();

    void on_btnBack_3_clicked();

    void on_btnNew_clicked();

private:
    void resizeEvent(QResizeEvent *event);
    Ui::S_InventoryManager *ui;
};

#endif // S_INVENTORYMANAGER_H
