#include "s_manufacture.h"
#include "ui_manufactureScreen.h"
#include "s_menu.h"

S_Manufacture::S_Manufacture(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Manufacture)
{
    ui->setupUi(this);
}

S_Manufacture::~S_Manufacture()
{
    delete ui;
}

void S_Manufacture::on_btnMenu_clicked()
{
    this->hide();
    S_Menu menu;
    menu.setModal(true);
    // menu.showFullScreen();
    menu.exec();

}
