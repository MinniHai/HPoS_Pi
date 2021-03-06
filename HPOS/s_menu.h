#ifndef MENU_H
#define MENU_H

#include <QDialog>

#include "QTimer"
#include "QDateTime"
#include <QDebug>


namespace Ui {
    class Menu;
}

class S_Menu : public QDialog
{
    Q_OBJECT

public:
    static S_Menu *s_instance;
    static S_Menu *instance();
    explicit S_Menu(QWidget *parent = 0);
    ~S_Menu();
    void showFull();
    void setRole(bool isAdmin);
private slots:
    void on_btnLogout_clicked();
    void getTimer();
    void on_btnOrder_clicked();

    void on_btnHumanResource_clicked();

    void on_btnInventory_clicked();
    void on_btnCheckout_clicked();

private:
    Ui::Menu *ui;
};

#endif // MENU_H
