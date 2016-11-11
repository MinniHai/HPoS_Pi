#include "s_login.h"
#include "e_user.h"
#include "session.h"
#include "s_menu.h"
#include "keyboard.h"
#include <QMessageBox>

S_Login *S_Login::s_instance;
S_Login *S_Login::instance()
{
    if(!s_instance)
    {
        s_instance = new S_Login();
    }
    return s_instance;
}

S_Login::S_Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    connect(ui->ledPassword, SIGNAL(selectionChanged()), SLOT(runKeyboard()));
}

S_Login::~S_Login()
{
    delete ui;
}

void S_Login::login()
{
    if(ui->ledPassword->text().length() > 1)
    {
        E_User *user = new E_User();
        user  = user->getUserByPincode(ui->ledPassword->text());
        if(user != NULL)
        {
            if(user->stateID == Active)
            {
                Session::instance()->setUserSession((E_User *)user);
                // chuyển màn hình sang main menu
                S_Menu *menu = S_Menu::instance();
                menu->setModal(true);
                menu->showFull();
                this->close();
            }
            else
            {
                QMessageBox msBox;
                msBox.setText("Your account is not actived.");
                msBox.exec();
            }
        }
        else
        {
            QMessageBox msBox;
            msBox.setText("Login Failed.Pincode is invalid.");
            msBox.exec();
        }
    }
}

void S_Login::on_btnLogin_clicked()
{
    login();
}

void S_Login::runKeyboard()
{
    QLineEdit *line = (QLineEdit *)sender();
    line->setEchoMode(QLineEdit::Password);
    line->setPlaceholderText("Enter Pincode");
    Keyboard *keyboard = Keyboard::instance();
    keyboard->setLineEdit(line);
    keyboard->showFullScreen();
}
