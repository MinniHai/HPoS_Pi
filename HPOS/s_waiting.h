#ifndef WAITING_H
#define WAITING_H

#include <QMainWindow>

namespace Ui {
    class Waiting;
}

class S_Waiting : public QMainWindow
{
    Q_OBJECT

public:
    explicit S_Waiting(QWidget *parent = 0);
    ~S_Waiting();


private:
    Ui::Waiting *ui;
};

#endif // WAITING_H
