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
#include "e_role.h"
#include <QPixmap>
#include "e_state.h"
#include "utils.h"
#include "barcodescanner.h"
#include <QRegExpValidator>


S_UserDetail *S_UserDetail::s_instance;


S_UserDetail *S_UserDetail::instance()
{
    if(!s_instance)
    {
        s_instance = new S_UserDetail();
    }
    return s_instance;
}

S_UserDetail::S_UserDetail(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::S_UserDetail)
{
    ui->setupUi(this);

    listState = E_State::getAllState();

    foreach(E_State *item, listState)
    {
        ui->cbState->addItem(item->state, QVariant(item->stateID));
    }

    image = new  CustomeQlabel("", ui->frame);
    image->setObjectName("image");
    image->setGeometry(0, 0, 151, 201);
    image->setAlignment(Qt::AlignCenter);
    image->setPixmap(QPixmap(":/images/images/camera.png").scaled(QSize(120, 120)));

    QRegExp date("((19|20)\\d\\d)-(0?[1-9]|1[012])-(0?[1-9]|[12][0-9]|3[01])");
    QRegExpValidator *dateVal = new QRegExpValidator(date);
    ui->ledDOB->setValidator(dateVal);
    ui->ledDOB->setInputMask("9999-99-99");
    fillRolesData();

    connect(ui->ledFirstName, SIGNAL(selectionChanged()), SLOT(runKeyboard()));
    connect(ui->ledLastName, SIGNAL(selectionChanged()), SLOT(runKeyboard()));
    connect(ui->ledIdCard, SIGNAL(selectionChanged()), SLOT(runKeyboard()));
    connect(ui->ledDOB, SIGNAL(selectionChanged()), SLOT(runKeyboard()));
    connect(ui->ledPhone, SIGNAL(selectionChanged()), SLOT(runKeyboard()));
    connect(ui->ledPinCode, SIGNAL(selectionChanged()), SLOT(runKeyboard()));
    connect(image, SIGNAL(clicked()), SLOT(capture()));
}

void S_UserDetail::setUserDetail(E_User *user)
{
    this->user = user;
    fillDataUserDetail();
}


void S_UserDetail::capture()
{
    BarcodeScanner *capturer = BarcodeScanner::instance();
    if(capturer->timer->isActive())
    {
        capturer->isCapture = true;
        QHash<QString, QString> userHash ;
        userHash.insert("pictureUrl", capturer->imagePath);
        user->picUrl = capturer->imagePath;
        if(E_User::upateUser(userHash, user->userID))
        {
            //TODO: update user picUrl
        }
    }
    else
    {

        QString path ;
        if(!user->userID.isEmpty())
        {
            path = "Image/User/"
                   + user->userID
                   + ".png";
        }
        else
        {
            path = "Image/User/tmp.png";
        }
        QDir dir("Image/User");
        if(!dir.exists())
        {
            dir.mkpath(".");
        }
        capturer->capturePicture(path, image);
    }
}
void S_UserDetail::fillDataUserDetail()
{
    if(user)
    {
        ui->ledFirstName->setText(user->firstname);
        ui->ledIdCard->setText(user->idCard);
        ui->ledLastName->setText(user->lastname);
        ui->ledPhone->setText(user->phone);
        ui->ledPinCode->setText(user->pincode);
        ui->ledDOB->setText(user->DOB);
        ui->cbRoles->setCurrentIndex(ui->cbRoles->findText(user->roleType->roleType));
        ui->ledActiveTime->setText(user->activeTime);
        ui->ledEndTime->setText(user->endTime);
        ui->cbState->setCurrentIndex(ui->cbState->findText(user->state->state));
        ui->ledPwd->setText(user->pwd);
        if(!user->picUrl.isEmpty())
        {
            image->setPixmap(QPixmap(QDir::currentPath() + "/" + user->picUrl).scaled(image->size()));
        }
    }
}

S_UserDetail::~S_UserDetail()
{
    delete ui;
}

void S_UserDetail::fillRolesData()
{
    QList<E_Role *> listRoles = E_Role::getAllRole();
    foreach(E_Role *item, listRoles)
    {
        ui->cbRoles->addItem(item->roleType, QVariant(item->roleID));
        qDebug() << item->roleType;
    }
}

void S_UserDetail::clearAll()
{
    ui->ledFirstName->setText("");
    ui->ledIdCard->setText("");
    ui->ledLastName->setText("");
    ui->ledPhone->setText("");
    ui->ledPinCode->setText("");
    ui->ledDOB->setText("");
    ui->cbRoles->setCurrentIndex(1);
    image->setEnabled(true);
    image->setPixmap(QPixmap(":/images/images/camera.png").scaled(QSize(120, 120)));
}

void S_UserDetail::on_btnMenu_clicked()
{
    S_Menu *menu = S_Menu::instance();
    menu->setModal(true);
    menu->showFull();
    this->close();
}

void S_UserDetail::on_btnBack_clicked()
{
    S_UserManager *user = new S_UserManager();
    user->setModal(true);
    user->listUser = E_User::getAllUser();
    user->setDataToTable();
    user->showFullScreen();
    this->close();
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
    QHash<QString, QString> userHash;
    userHash.insert("firstName", ui->ledFirstName->text());
    userHash.insert("lastName", ui->ledLastName->text());
    userHash.insert("phone", ui->ledPhone->text());
    userHash.insert("pinCode", ui->ledPinCode->text());
    userHash.insert("roleID", ui->cbRoles->currentData().toString());
    userHash.insert("idCard", ui->ledIdCard->text());
    userHash.insert("DOB", ui->ledDOB->text());
    userHash.insert("pwd", ui->ledPwd->text());
    userHash.insert("stateID", ui->cbState->currentData().toString());
    if(action == Insert)
    {
        QString newPath =  "Image/User/"
                           + QString::number(E_User::getMaxID() + 1)
                           + ".png";
        userHash.insert("pictureUrl", newPath);
        BarcodeScanner::instance()->movePicture(user->picUrl, newPath);
        user->picUrl = newPath;
        qDebug() << newPath;
        if(E_User::insertUser(userHash))
        {
            QMessageBox box ;
            box.setText("Insert Done!");
            QPushButton *ok = box.addButton(QMessageBox::Ok);
            box.exec();
            if(box.clickedButton() == ok)
            {
                on_btnBack_clicked();
            }

        }
        else
        {
            QMessageBox::information(this, "Insert ", "Insert Failed!");
        }
    }
    else
    {
        if(E_User::upateUser(userHash, this->user->userID))
        {
            userHash.insert("pictureUrl", user->picUrl);
            QMessageBox box ;
            box.setText("Update Done!");
            QPushButton *ok = box.addButton(QMessageBox::Ok);
            box.exec();
            if(box.clickedButton() == ok)
            {
                on_btnBack_clicked();
            }
        }
        else
        {
            QMessageBox::information(this, "Update ", "Update Failed!");
        }
    }
}

void S_UserDetail::on_btnClear_clicked()
{
    if(action == S_UserDetail::Insert)
    {
        clearAll();
    }
    else
    {
        fillDataUserDetail();
    }
}
