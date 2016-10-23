#include "s_usermanager.h"
#include "ui_s_usermanager.h"

S_UserManager::S_UserManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::S_UserManager)
{
    ui->setupUi(this);
}

S_UserManager::~S_UserManager()
{
    delete ui;
}
