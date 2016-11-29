#ifndef S_USERDETAIL_H
#define S_USERDETAIL_H

#include <QDialog>
#include <QDateEdit>
#include "customeqlabel.h"
#include "customelineedit.h"

class E_User;
class E_State;

namespace Ui {
    class S_UserDetail;
}



class S_UserDetail : public QDialog
{
    Q_OBJECT
    //    Q_ENUMS(Action)

public:
    enum Action
    {
        Insert,
        Update
    };
    static S_UserDetail *s_instance;
    static S_UserDetail *instance();

    explicit S_UserDetail(QWidget *parent = 0);
    ~S_UserDetail();

    Action action;
    CustomeQlabel *image;

    QList<E_State *> listState;
    void setUserDetail(E_User *user);
    E_User *user;
    void clearAll();

private slots:
    void on_btnMenu_clicked();

    void on_btnBack_clicked();

    void runKeyboard();

    void on_btnSave_clicked();

    void on_btnClear_clicked();

    void capture();

private:
    void fillLayout();
    bool eventFilter(QObject *obj, QEvent *event);

    CustomeLineEdit *ledFirstName;
    CustomeLineEdit *ledLastName;
    CustomeLineEdit *ledIdCard;
    QDateEdit *ledDOB;
    CustomeLineEdit *ledPhone;
    CustomeLineEdit *ledPinCode;
    CustomeLineEdit *ledPwd;

    QComboBox *cbState;
    QLineEdit *ledActiveTime;
    QLineEdit *ledEndTime;


    Ui::S_UserDetail *ui;
    void fillRolesData();
    void fillDataUserDetail();
};

#endif // S_USERDETAIL_H
