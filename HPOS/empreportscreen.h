#ifndef EMPREPORTSCREEN_H
#define EMPREPORTSCREEN_H

#include <QDialog>

namespace Ui {
class EmpReportScreen;
}

class EmpReportScreen : public QDialog
{
    Q_OBJECT

public:

    static EmpReportScreen *s_instance;
    static EmpReportScreen *instance();

    explicit EmpReportScreen(QWidget *parent = 0);
    ~EmpReportScreen();

private:
    Ui::EmpReportScreen *ui;
};

#endif // EMPREPORTSCREEN_H
