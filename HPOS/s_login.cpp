#include "s_login.h"
#include "e_user.h"
#include "session.h"
#include "s_menu.h"
#include "keyboard.h"

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
            Session::instance()->setUserSession((E_User *)user);
            qDebug() << Session::instance()->getUserSession()->getUserName();
            // chuyển màn hình sang main menu
            S_Menu *menu = S_Menu::instance();
            menu->setModal(true);
            menu->showFull();
            this->close();
            menu->exec();
        }
        else
        {
            //TODO: Add notification :Login Fail.
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
