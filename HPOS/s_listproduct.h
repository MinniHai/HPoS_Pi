#ifndef LISTPRODUCT_H
#define LISTPRODUCT_H

#include <QDialog>

namespace Ui {
    class ListProduct;
}

class S_ListProduct : public QDialog
{
    Q_OBJECT

public:
    explicit S_ListProduct(QWidget *parent = 0);
    ~S_ListProduct();

private:
    Ui::ListProduct *ui;
};

#endif // LISTPRODUCT_H
