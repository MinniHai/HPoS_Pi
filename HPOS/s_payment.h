#ifndef PAYMENT_H
#define PAYMENT_H

#include <QDialog>

namespace Ui {
    class Payment;
}

class S_Payment : public QDialog
{
    Q_OBJECT

public:
    static S_Payment *s_instance;
    static S_Payment *instance();
    explicit S_Payment(QWidget *parent = 0);
    ~S_Payment();

    void fillData();
private slots:
    void on_btnBack_clicked();

    void on_btnCheckOK_clicked();

    void calculate();
private:
    Ui::Payment *ui;
};

#endif // PAYMENT_H
