#include "empreportscreen.h"
#include "ui_empreportscreen.h"


EmpReportScreen *EmpReportScreen::s_instance;


EmpReportScreen *EmpReportScreen::instance()
{
    if(!s_instance)
    {
        s_instance = new EmpReportScreen();
    }
    return s_instance;
}


EmpReportScreen::EmpReportScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EmpReportScreen)
{
    ui->setupUi(this);

}

EmpReportScreen::~EmpReportScreen()
{
    delete ui;
}
