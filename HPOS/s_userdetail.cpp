#include "s_userdetail.h"
#include "ui_userdetail.h"

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
