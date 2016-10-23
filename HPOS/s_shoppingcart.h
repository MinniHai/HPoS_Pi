#ifndef LISTPRODUCT_H
#define LISTPRODUCT_H

#include <QDialog>

namespace Ui {
    class ShoppingCart;
}

class S_ShoppingCart : public QDialog
{
    Q_OBJECT

public:
    explicit S_ShoppingCart(QWidget *parent = 0);
    ~S_ShoppingCart();

private:
    Ui::ShoppingCart *ui;
};

#endif // LISTPRODUCT_H
