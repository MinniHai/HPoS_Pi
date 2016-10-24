#ifndef S_USERDETAIL_H
#define S_USERDETAIL_H

#include <QDialog>

namespace Ui {
class S_UserDetail;
}

class S_UserDetail : public QDialog
{
    Q_OBJECT

public:
    explicit S_UserDetail(QWidget *parent = 0);
    ~S_UserDetail();

private:
    Ui::S_UserDetail *ui;
};

#endif // S_USERDETAIL_H
