#ifndef CHECKOUT_H
#define CHECKOUT_H

#include <QDialog>
#include <QTableWidgetItem>

namespace Ui {
    class Checkout;
}

class S_Checkout : public QDialog
{
    Q_OBJECT

public:

    void resizeEvent(QResizeEvent *event);
    QTableWidgetItem *createTableWidgetItem(const QString &text) const;
    static S_Checkout *s_instance;
    static S_Checkout *instance();
    explicit S_Checkout(QWidget *parent = 0);
    ~S_Checkout();

private slots:
    void on_btnBack_clicked();

    void on_btnAdd_clicked();

    void on_btnCheckOK_clicked();


private:
    Ui::Checkout *ui;
};

#endif // CHECKOUT_H
