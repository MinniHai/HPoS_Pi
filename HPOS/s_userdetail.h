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

private slots:
    void on_btnMenu_clicked();

    void on_btnBack_clicked();

    void runKeyboard();

private:
    Ui::S_UserDetail *ui;
};

#endif // S_USERDETAIL_H
