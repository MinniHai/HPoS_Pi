#include "s_usermanager.h"
#include "ui_s_usermanager.h"
#include "e_user.h"
#include "e_role.h"
#include "s_menu.h"
#include "s_userdetail.h"
#include "keyboard.h"
#include <QResizeEvent>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDebug>






S_UserManager::S_UserManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::S_UserManager)
{
    ui->setupUi(this);
    connect(ui->ledSearch, SIGNAL(selectionChanged()), SLOT(runKeyboard()));

}

S_UserManager::~S_UserManager()
{
    delete ui;
}
void S_UserManager::resizeEvent(QResizeEvent *event)
{
    int width =  480;
    ui->tblListUser->setColumnWidth(0, width * 4 / 12);
    ui->tblListUser->setColumnWidth(1, width * 2 / 12);
    ui->tblListUser->setColumnWidth(2, width * 5 / 12);
    ui->tblListUser->setColumnWidth(3, width * 0.95 / 12);
//TODO: scroll off
}
void S_UserManager::showScreen()
{
    E_User *user = new E_User();
    listUser = user->getAllUser();
    if (!listUser.isEmpty())
    {
        for (int i = 0; i < listUser.size(); i++)
        {
            ui->tblListUser->insertRow(i);
            ui->tblListUser->setItem(i, 0, createTableWidgetItem(listUser[i]->username));
            ui->tblListUser->setItem(i, 1, createTableWidgetItem(listUser[i]->roleType->roleType));
            ui->tblListUser->setItem(i, 2, createTableWidgetItem(listUser[i]->phone));
            //
            QWidget *pWidget = new QWidget();
            QPushButton *btn_edit = new QPushButton();
            btn_edit->setText("Edit");
            btn_edit->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
            //        btn_edit->setStyleSheet("background-color:black");
            QHBoxLayout *pLayout = new QHBoxLayout(pWidget);
            pLayout->addWidget(btn_edit);
            pLayout->setAlignment(Qt::AlignHCenter);
            pLayout->setContentsMargins(0, 0, 0, 0);
            pWidget->setLayout(pLayout);
            ui->tblListUser->setCellWidget(i, 3, pWidget);


        }
    }
    this->showFullScreen();
}
QTableWidgetItem *S_UserManager::createTableWidgetItem(const QString &text) const
{
    QTableWidgetItem *item = new QTableWidgetItem(text);
    item->setTextAlignment(Qt::AlignCenter);
    return item;
}

void S_UserManager::on_btnMenu_clicked()
{
    S_Menu menu;
    menu.setModal(true);
    menu.showFullScreen();
    menu.exec();
    this->hide();
}

void S_UserManager::on_btnSearch_clicked()
{

}

void S_UserManager::on_btnNew_clicked()
{
    this->hide();
    S_UserDetail userdetail;
    userdetail.setModal(true);
    userdetail.showFullScreen();
    userdetail.exec();
}

void S_UserManager::on_btnBack_clicked()
{
    S_Menu menu;
    menu.setModal(true);
    menu.showFullScreen();
    menu.exec();
    this->hide();
}

void S_UserManager::runKeyboard()
{
    Keyboard *keyboard = Keyboard::instance();
    QLineEdit *line = ui->ledSearch;
    keyboard->setLineEdit(line);
    keyboard->setWindowModality(Qt::WindowModal);
    keyboard->showFullScreen();
}

void S_UserManager::on_btnDelete_clicked()
{

}
