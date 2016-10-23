#ifndef UTILS_H
#define UTILS_H
#include<QSqlDatabase>
#include<QtSql>
#include<qsqldatabase.h>
class Utils
{

public:
    static Utils *s_instance;
    static Utils *instance();

    QSqlDatabase *getDB();
    bool isDebugging();
    void showMessageBox();
    Utils();
    QSqlDatabase *database;
protected:
private:
    bool is_Debug;
    QString dbDriver;
    QString dbHostName ;
    QString dbName;
    QString dbUsername ;
    QString dbPwd ;
    int dbPort;


    /*for(int i = 0; i < 3; i++)
    {
        ui->table->insertRow(i);
        ui->table->setItem(i, 0, new QTableWidgetItem("mot"));
        ui->table->setItem(i, 1, new QTableWidgetItem("hai"));
        QWidget *pWidget = new QWidget();
        QPushButton *btn_edit = new QPushButton();
        btn_edit->setText("Edit");
        btn_edit->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        //        btn_edit->setStyleSheet("background-color:black");
        QHBoxLayout *pLayout = new QHBoxLayout(pWidget);
        pLayout->addWidget(btn_edit);
        pLayout->setAlignment(Qt::AlignHCenter);
        pLayout->setContentsMargins(0, 0, 0, 0);
        pWidget->setLayout(pLayout);
        ui->table->setCellWidget(i, 2, pWidget);
        connect(btn_edit, SIGNAL(clicked(bool)), SLOT(edit()));
    }
     *
     *
     *
     *
     *
     */
};
#endif // UTILS_H
