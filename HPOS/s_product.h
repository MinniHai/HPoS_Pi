#ifndef PRODUCT_H
#define PRODUCT_H

#include <QDialog>
class E_Product;
class CustomeQlabel;

namespace Ui {
    class Product;
}

class S_Product : public QDialog
{
    Q_OBJECT

public:
    static S_Product *s_instance;
    static S_Product *instance();

    explicit S_Product(QWidget *parent = 0);
    ~S_Product();

    E_Product *product;
    void setProduct(E_Product *product);
    void setEnabled(bool);
    void viewInformation(E_Product *product);
private slots:
    void on_btnMenu_clicked();

    void on_btnAddManufacture_clicked();

private:
    CustomeQlabel *image;
    Ui::Product *ui;
};

#endif // PRODUCT_H
