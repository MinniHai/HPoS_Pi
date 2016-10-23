#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "ui_loginScreen.h"
#include <QDebug>

namespace Ui {
    class Login;
}

class S_Login : public QDialog
{
    Q_OBJECT

public:
    static S_Login *s_instance;
    static S_Login *instance();

    explicit S_Login(QWidget *parent = 0);
    ~S_Login();

private slots:
    void on_btnLogin_clicked();
    void runKeyboard();

private:
    void login();
    Ui::Login *ui;
};

#endif // LOGIN_H
