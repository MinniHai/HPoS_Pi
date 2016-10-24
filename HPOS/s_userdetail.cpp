#include "s_userdetail.h"
#include "ui_userdetail.h"
#include "s_menu.h"
#include "s_usermanager.h"

S_UserDetail::S_UserDetail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::S_UserDetail)
{
    ui->setupUi(this);
}

S_UserDetail::~S_UserDetail()
{
    delete ui;
}

void S_UserDetail::on_btnMenu_clicked()
{
    this->close();
    S_Menu menu;
    menu.setModal(true);
    menu.showFullScreen();
    menu.exec();
}

void S_UserDetail::on_btnBack_clicked()
{
    this->hide();
    S_UserManager usermanager;
    usermanager.setModal(true);
    usermanager.showFullScreen();
    usermanager.exec();
}
