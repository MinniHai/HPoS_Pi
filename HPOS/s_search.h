#ifndef ORDER_H
#define ORDER_H

#include <QDialog>
#include <QTimer>
#include <QLabel>
#include <QLineEdit>

class BarcodeScanner;
class CustomeQlabel;
class E_Product;

namespace Ui {
    class Search;
}

class S_Search : public QDialog
{
    Q_OBJECT

public:
    static S_Search *s_instance;
    static S_Search *instance();
    bool isValidBarcode(QString barcode);
    QLineEdit *txtSearch;
    enum  Action
    {
        Update, Insert, View, Shopping
    };

    explicit S_Search(QWidget *parent = 0);
    bool searchByBarcode(QString barcode);
    void scanBarcode();
    Action action;

    void setState(Action newAction);
    CustomeQlabel *lbStatus;
    CustomeQlabel *lbScan;
    ~S_Search();
signals:

public slots:

    void checkStatus();

    void viewInformation();

    void setBackToDefaul();

private slots:
    void on_btnPlus_clicked();

    void on_btnMinus_clicked();

    void on_btnBack_clicked();

    void on_btnCheckout_clicked();

    void on_btnMenu_clicked();

    void on_btnAdd_clicked();

    void search_textChange(const QString &);

    void runKeyboard();

    void on_btnSearch_clicked();

private:
    bool isScanned;
    E_Product *product;
    BarcodeScanner *bc;
    QTimer *timer;
    int value ;
    int number;
    bool isSet;
    Ui::Search *ui;
};

#endif // ORDER_H
