#ifndef PRODUCT_H
#define PRODUCT_H

#include <QDialog>
#include <QList>
#include "customelineedit.h"
class E_Product;
class E_Barcode;
class CustomeQlabel;
class E_Category;

namespace Ui {
    class Product;
}

class S_Product : public QDialog
{
    Q_OBJECT

public:
    static S_Product *s_instance;
    static S_Product *instance();

    enum Action
    {
        Update, Insert, View, InsertMore, UpdateCart
    };

    Action action;
    explicit S_Product(QWidget *parent = 0);
    ~S_Product();


    QList<E_Product *>productList;
    E_Product *product;
    E_Barcode *barcode;
    void setProduct(E_Product *product);
    void setEnabled(bool);
    void setBarcode(E_Barcode *barcode);
    void clearAll();
    void viewInformation(E_Product *productTmp);
    void refreshManufacturer();
    void setQuantityText(int quantity);

public slots:
    void viewInformation(int currentIndext);
    void capture();
private slots:
    void runKeyboard();

    void on_btnMenu_clicked();

    void btnAddManufacture_click();

    void on_btnClear_clicked();

    void on_btnSave_clicked();

    void on_btnBack_clicked();

    void on_btnKeyboard_clicked();

private:
    void fillLayout();

    QLineEdit *lineName;
    CustomeLineEdit *cbPro;
    QList<E_Category *> cateList;
    CustomeQlabel *image;
    Ui::Product *ui;
    CustomeLineEdit *ledCountry;
    CustomeLineEdit *ledManufacture;
    CustomeLineEdit *ledPrice;
    CustomeLineEdit *ledQuantity;
    QComboBox *cbCategory;
    QToolButton *btnAddManufacture;

};

#endif // PRODUCT_H
