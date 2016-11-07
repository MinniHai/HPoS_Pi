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
#include <QSignalMapper>
#include <QItemSelection>
#include <QModelIndex>
#include "e_state.h"

S_UserManager *S_UserManager::s_instance;


S_UserManager *S_UserManager::instance()
{
    if(!s_instance)
    {
        s_instance = new S_UserManager();
    }
    return s_instance;
}

S_UserManager::S_UserManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::S_UserManager)
{
    ui->setupUi(this);
    listUser = E_User::getAllUser();
    listState = E_State::getAllState();

    foreach(E_State *item, listState)
    {
        ui->cbbSearchType->addItem(item->state, QVariant(item->stateID));
    }

    ui->btnDelete->setEnabled(false);
    ui->tblListUser->setSelectionMode(QAbstractItemView::MultiSelection);
    ui->tblListUser->setSelectionBehavior(QAbstractItemView::SelectRows);
    connect(ui->ledSearch, SIGNAL(selectionChanged()), SLOT(runKeyboard()));
    connect(ui->ledSearch, SIGNAL(textChanged(QString)), SLOT(search()));
    connect(ui->cbbSearchType, SIGNAL(currentIndexChanged(int)), SLOT(search()));

}

S_UserManager::~S_UserManager()
{
    delete ui;
}
void S_UserManager::resizeEvent(QResizeEvent *)
{
    int width =  480;
    ui->tblListUser->setColumnWidth(0, width * 4 / 15);
    ui->tblListUser->setColumnWidth(1, width * 4 / 15);
    ui->tblListUser->setColumnWidth(2, width * 2 / 15);
    ui->tblListUser->setColumnWidth(3, width * 4 / 15);
    ui->tblListUser->setColumnWidth(4, width * 0.95 / 15);
    //TODO: scroll off
}
void S_UserManager::setDataToTable()
{
    ui->tblListUser->clearContents();
    ui->tblListUser->setRowCount(0);
    if(!listUser.isEmpty())
    {
        QSignalMapper *mapper = new QSignalMapper(this);
        for(int i = 0; i < listUser.size(); i++)
        {
            ui->tblListUser->insertRow(i);
            ui->tblListUser->setItem(i, 0, createTableWidgetItem(listUser[i]->firstname));
            ui->tblListUser->setItem(i, 1, createTableWidgetItem(listUser[i]->lastname));
            ui->tblListUser->setItem(i, 2, createTableWidgetItem(listUser[i]->roleType->roleType));
            ui->tblListUser->setItem(i, 3, createTableWidgetItem(listUser[i]->phone));
            //
            QWidget *pWidget = new QWidget();
            QPushButton *btn_edit = new QPushButton("Remove");
            btn_edit->setText("Edit");
            btn_edit->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
            //        btn_edit->setStyleSheet("background-color:black");
            QHBoxLayout *pLayout = new QHBoxLayout(pWidget);
            pLayout->addWidget(btn_edit);
            pLayout->setAlignment(Qt::AlignHCenter);
            pLayout->setContentsMargins(0, 0, 0, 0);
            pWidget->setLayout(pLayout);
            ui->tblListUser->setCellWidget(i, 4, pWidget);
            mapper->setMapping(btn_edit, i);
            connect(btn_edit, SIGNAL(clicked(bool)), mapper, SLOT(map()));

        }
        connect(mapper, SIGNAL(mapped(int)), this, SLOT(edit_clicked(int)));
        connect(ui->tblListUser, SIGNAL(cellClicked(int, int)), SLOT(cell_click(int, int)));
    }
    else
    {
        qDebug() << "list is empty!" ;
    }

}

void S_UserManager::cell_click(int row, int column)
{
    qDebug() << QString::number(row) + " : " + QString::number(column);
}

void S_UserManager::edit_clicked(int row)
{
    S_UserDetail *userDetail = S_UserDetail::instance();
    userDetail->action = S_UserDetail::Update;
    userDetail->setUserDetail(listUser[row]);
    userDetail->setModal(true);
    userDetail->image->setFocus();
    userDetail->showFullScreen();
    this->close();
}

QTableWidgetItem *S_UserManager::createTableWidgetItem(const QString &text) const
{
    QTableWidgetItem *item = new QTableWidgetItem(text);
    item->setTextAlignment(Qt::AlignCenter);
    return item;
}

void S_UserManager::on_btnMenu_clicked()
{
    S_Menu *menu = S_Menu::instance();
    menu->setModal(true);
    menu->showFull();
    this->close();
}


void S_UserManager::on_btnNew_clicked()
{
    S_UserDetail *userdetail = S_UserDetail::instance();
    userdetail->setModal(true);
    userdetail->clearFocus();
    userdetail->clearAll();
    userdetail->user = new  E_User();
    userdetail->action = S_UserDetail::Insert;
    userdetail->showFullScreen();
    this->close();
}

void S_UserManager::on_btnBack_clicked()
{
    on_btnMenu_clicked();
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
    QItemSelection selection(ui->tblListUser->selectionModel()->selection());

    qDebug() <<  selection.indexes().size();
    QList<int > listDelete;

    foreach(QModelIndex item, selection.indexes())
    {
        if(!listDelete.contains(item.row()))
        {
            listDelete.append(item.row());
        }
    }
    foreach(int item, listDelete)
    {
        if(E_User::deleteUser(listUser.at(item)->userID))
        {
            qDebug() << "delete successfull!";
        }
    }

}



void S_UserManager::search()
{
    listUser = E_User::SearchByUserName(ui->ledSearch->text(), ui->cbbSearchType->currentData().toString());
    setDataToTable();
}
