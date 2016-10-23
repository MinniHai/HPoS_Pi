#ifndef S_USERMANAGER_H
#define S_USERMANAGER_H

#include <QDialog>

namespace Ui {
class S_UserManager;
}

class S_UserManager : public QDialog
{
    Q_OBJECT

public:
    explicit S_UserManager(QWidget *parent = 0);
    ~S_UserManager();

private:
    Ui::S_UserManager *ui;
};

#endif // S_USERMANAGER_H
