#include "s_waiting.h"
#include "ui_waitingScreen.h"
#include <QMovie>
#include "s_login.h"

S_Waiting::S_Waiting(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Waiting)
{
    ui->setupUi(this);
    QMovie *waiting = new QMovie(":/images/images/WhiteLoader.gif");
    ui->lblwaiting->setMovie(waiting);
    waiting->start();

}

S_Waiting::~S_Waiting()
{
    delete ui;
}

