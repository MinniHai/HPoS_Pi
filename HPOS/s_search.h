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

    explicit S_Search(QWidget *parent = 0);
    void searchByBarcode(QString barcode);
    CustomeQlabel *lbStatus;
    CustomeQlabel *lbScan;
    ~S_Search();
public slots:
    void checkStatus();
    void viewInfomation();

private slots:
    void on_btnPlus_clicked();

    void on_btnMinus_clicked();

    void on_btnBack_clicked();

    void on_btnCheckout_clicked();

    void on_btnMenu_clicked();

    void on_btnAdd_clicked();

    void search_textChange(const QString &);

    void runKeyboard();

private:
    E_Product *product;
    void setBackToDefaul();
    BarcodeScanner *bc;
    QTimer *timer;
    int value ;
    int number;
    bool isSet;
    Ui::Search *ui;
};

#endif // ORDER_H
