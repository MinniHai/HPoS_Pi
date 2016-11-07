#ifndef CHECKOUT_H
#define CHECKOUT_H

#include <QDialog>
#include <QTableWidgetItem>
#include <QResizeEvent>

namespace Ui {
    class Checkout;
}

class S_Checkout : public QDialog
{
    Q_OBJECT

public:
    enum Action
    {
        View, Shopping
    };

    static S_Checkout *s_instance;
    static S_Checkout *instance();

    void resizeEvent(QResizeEvent *event);
    QTableWidgetItem *createTableWidgetItem(const QString &text) const;
    void showDataToTable();
    explicit S_Checkout(QWidget *parent = 0);
    ~S_Checkout();

    Action action;
private slots:
    void edit_clicked(int row);
    void cell_click(int row, int column);
    void on_btnBack_clicked();

    void on_btnAdd_clicked();

    void on_btnCheckOK_clicked();


    void on_btnMenu_clicked();

    void on_btnSearch_clicked();

private:
    Ui::Checkout *ui;
};

#endif // CHECKOUT_H
