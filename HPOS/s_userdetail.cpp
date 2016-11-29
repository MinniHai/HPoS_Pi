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
#include <QGridLayout>
#include <QCalendarWidget>


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
    ledDOB = new QDateEdit();
    ledDOB->setCalendarPopup(true);
    ledDOB->setDisplayFormat("yyyy-MM-dd");
    ledDOB->setMinimumDate(QDate(1970,01,01));
    ledDOB->setMaximumDate(QDate::currentDate());
    ledDOB->calendarWidget()->installEventFilter(this);
    ledDOB->setDate(QDate::fromString("2000-01-01","yyyy-MM-dd"));
//    ledDOB->calendarWidget()->setSelectedDate(QDate::fromString("2000-01-01","yyyy-MM-dd"));

    ledFirstName = new CustomeLineEdit();
    ledFirstName->setClearButtonEnabled(true);
    ledIdCard = new CustomeLineEdit();
    ledIdCard->setClearButtonEnabled(true);
    ledLastName  = new CustomeLineEdit();
    ledLastName->setClearButtonEnabled(true);
    ledPinCode = new CustomeLineEdit();
    ledPinCode->setClearButtonEnabled(true);
    ledPhone = new CustomeLineEdit();
    ledPhone->setClearButtonEnabled(true);
    ledPwd = new CustomeLineEdit();
    ledPwd->setClearButtonEnabled(true);

    cbState = new QComboBox();
    ledActiveTime = new QLineEdit();
    ledEndTime = new QLineEdit();

    foreach(E_State *item, listState)
    {
        cbState->addItem(item->state, QVariant(item->stateID));
    }

    image = new  CustomeQlabel("", ui->frame);
    image->setObjectName("image");
    image->setGeometry(0, 0, 151, 201);
    image->setAlignment(Qt::AlignCenter);
    image->setPixmap(QPixmap(":/images/images/camera.png").scaled(QSize(120, 120)));

//    QRegExp date("((19|20)\\d\\d)-(0?[1-9]|1[012])-(0?[1-9]|[12][0-9]|3[01])");
//    QRegExpValidator *dateVal = new QRegExpValidator(date);
//    ledDOB->setValidator(dateVal);
    //    ledDOB->setInputMask("9999-99-99");
    connect(image, SIGNAL(clicked()), SLOT(capture()));
    fillRolesData();
    fillLayout();
}

bool S_UserDetail::eventFilter(QObject *obj, QEvent *event) {
    if(obj == ledDOB->calendarWidget() && event->type() == QEvent::Show){
        QPoint pos = ledDOB->mapToGlobal(ledDOB->geometry().bottomLeft());
        ledDOB->calendarWidget()->window()->move(pos.x() - 130,pos.y()-280);
    }
    return false;
}

void S_UserDetail::fillLayout(){

    QWidget *wget = new QWidget();
    QGridLayout *grid = new QGridLayout();
    grid->addWidget(new QLabel("First Name"),0,0);
    ledFirstName->setPlaceholderText("Enter FirstName");
    grid->addWidget(ledFirstName,1,0);
    grid->addWidget(new QLabel("Last Name"),2,0);
    ledLastName->setPlaceholderText("Enter LastName");
    grid->addWidget(ledLastName,3,0);
    grid->addWidget(new QLabel("Day Of Birth"),4,0);
//    ledDOB->setPlaceholderText("Form : yyyy-mm-dd");
    grid->addWidget(ledDOB,5,0);
    grid->addWidget(new QLabel("ID CARD"),6,0);
    ledIdCard->setPlaceholderText("Enter ID Card");
    grid->addWidget(ledIdCard,7,0);

    grid->addWidget(new QLabel("Phone Number"),8,0);
    ledPhone->setPlaceholderText("Phone Number");
    grid->addWidget(ledPhone,9,0);
    grid->addWidget(new QLabel("State"),10,0);
    grid->addWidget(cbState,11,0);
    grid->addWidget(new QLabel("Active Time"),12,0);
    ledActiveTime->setDisabled(true);
    grid->addWidget(ledActiveTime,13,0);
    ledEndTime->setDisabled(true);
    grid->addWidget(new QLabel("End Time"),14,0);
    grid->addWidget(ledEndTime,15,0);
    grid->addWidget(new QLabel("PIN Code"),16,0);
    ledPinCode->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    ledPinCode->setPlaceholderText("Enter PIN Code");
    grid->addWidget(ledPinCode,17,0);
    ledPwd->setPlaceholderText("Enter Password");
    ledPwd->setEchoMode(QLineEdit::PasswordEchoOnEdit);
    grid->addWidget(new QLabel("Password"),18,0);
    grid->addWidget(ledPwd,19,0);

    wget->setLayout(grid);
    ui->scrollArea->setWidget(wget);
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
        ledFirstName->setText(user->firstname);
        ledIdCard->setText(user->idCard);
        ledLastName->setText(user->lastname);
        ledPhone->setText(user->phone);
        ledPinCode->setText(user->pincode);
        ledDOB->setDate(QDate::fromString(user->DOB,"yyyy-MM-dd"));
        ui->cbRoles->setCurrentIndex(ui->cbRoles->findText(user->roleType->roleType));
        ledActiveTime->setText(user->activeTime.replace("T"," "));
        ledEndTime->setText(user->endTime.replace("T"," "));
        cbState->setCurrentIndex(cbState->findText(user->state->state));
        ledPwd->setText(user->pwd);
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
    ledFirstName->setText("");
    ledIdCard->setText("");
    ledLastName->setText("");
    ledPhone->setText("");
    ledPinCode->setText("");
//    ledDOB->setText("");
    ledDOB->setDate(QDate::fromString("2000-01-01","yyyy-MM-dd"));
    ui->cbRoles->setCurrentIndex(1);
    ledActiveTime->setText("");
    ledEndTime->setText("");
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
    userHash.insert("firstName", ledFirstName->text());
    userHash.insert("lastName", ledLastName->text());
    userHash.insert("phone", ledPhone->text());
    userHash.insert("pinCode", ledPinCode->text());
    userHash.insert("roleID", ui->cbRoles->currentData().toString());
    userHash.insert("idCard", ledIdCard->text());
    if(!ledDOB->text().isEmpty())
        userHash.insert("DOB", ledDOB->text());
    userHash.insert("pwd", ledPwd->text());
    userHash.insert("stateID", cbState->currentData().toString());
    userHash.insert("pictureUrl", user->picUrl);
    if(cbState->currentData().toInt() == 1 && user->activeTime.isEmpty()){
        userHash.insert("activeTime", Utils::instance()->getCurrentDateTime());
    }
    if(cbState->currentData().toInt() == 4 && user->endTime.isEmpty()) {
        userHash.insert("endTime",Utils::instance()->getCurrentDateTime());
    }

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
