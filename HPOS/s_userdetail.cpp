#include "s_userdetail.h"
#include "ui_userdetail.h"
#include "s_menu.h"
#include "s_usermanager.h"
#include <QHash>
#include <QDebug>
#include <QMessageBox>
#include <QHashIterator>
#include "keyboard.h"
#include "e_user.h"


S_UserDetail::S_UserDetail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::S_UserDetail)
{
    ui->setupUi(this);
    connect(ui->ledFirstName, SIGNAL(selectionChanged()), SLOT(runKeyboard()));
    connect(ui->ledLastName, SIGNAL(selectionChanged()), SLOT(runKeyboard()));
    connect(ui->ledIdCard, SIGNAL(selectionChanged()), SLOT(runKeyboard()));
    connect(ui->ledDOB, SIGNAL(selectionChanged()), SLOT(runKeyboard()));
    connect(ui->ledPhone, SIGNAL(selectionChanged()), SLOT(runKeyboard()));
    connect(ui->ledPinCode, SIGNAL(selectionChanged()), SLOT(runKeyboard()));
    connect(ui->ledRole, SIGNAL(selectionChanged()), SLOT(runKeyboard()));
}

S_UserDetail::~S_UserDetail()
{
    delete ui;
}

void S_UserDetail::on_btnMenu_clicked()
{
    S_Menu menu;
    menu.setModal(true);
    menu.showFullScreen();
    menu.exec();
    this->close();
}

void S_UserDetail::on_btnBack_clicked()
{

    S_UserManager usermanager;
    usermanager.setModal(true);
    usermanager.setDataToTable();
    usermanager.exec();
    this->hide();
}

void S_UserDetail::runKeyboard()
{
    Keyboard *keyboard = Keyboard::instance();
    QLineEdit *line = (QLineEdit *)sender();
    keyboard->setLineEdit(line);
    keyboard->setWindowModality(Qt::WindowModal);
    keyboard->showFullScreen();
}

void S_UserDetail::on_btnSave_clicked()
{
    QHash<QString, QString> user;
    user.insert("firstName", ui->ledFirstName->text());
    user.insert("lastName", ui->ledLastName->text());
    user.insert("phone", ui->ledPhone->text());
    user.insert("pinCode", ui->ledPinCode->text());
    user.insert("roleID", ui->ledRole->text());
    user.insert("idCard", ui->ledIdCard->text());
    user.insert("DOB", ui->ledDOB->text());
    if(E_User::insertUser(user))
    {
        qDebug() << "insert ok";
        QMessageBox::information(this, "Insert ", "Insert Done!");
    }
    else
    {
        QMessageBox::information(this, "Insert ", "Insert Failed!");
    }
}
