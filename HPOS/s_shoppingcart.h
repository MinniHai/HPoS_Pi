#ifndef LISTPRODUCT_H
#define LISTPRODUCT_H

#include <QDialog>

namespace Ui {
    class ShoppingCartScreen;
}

class S_ShoppingCart : public QDialog
{
    Q_OBJECT

public:
    static S_ShoppingCart *s_instance;
    static S_ShoppingCart *instance();
    explicit S_ShoppingCart(QWidget *parent = 0);
    ~S_ShoppingCart();

private:
    Ui::ShoppingCartScreen *ui;
};

#endif // LISTPRODUCT_H
