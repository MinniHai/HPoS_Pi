#ifndef MANUFACTURE_H
#define MANUFACTURE_H

#include <QDialog>

namespace Ui {
    class Manufacture;
}

class S_Manufacture : public QDialog
{
    Q_OBJECT

public:
    explicit S_Manufacture(QWidget *parent = 0);
    ~S_Manufacture();

private slots:
    void on_btnMenu_clicked();

private:
    Ui::Manufacture *ui;
};

#endif // MANUFACTURE_H
