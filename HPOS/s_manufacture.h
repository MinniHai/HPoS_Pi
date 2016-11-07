#ifndef MANUFACTURE_H
#define MANUFACTURE_H

#include <QDialog>
#include "customeqlabel.h"

class E_Manufacturer;
namespace Ui {
    class Manufacture;
}

class S_Manufacture : public QDialog
{
    Q_OBJECT

public:
    static S_Manufacture *s_instance;
    static S_Manufacture *instance();

    explicit S_Manufacture(QWidget *parent = 0);
    ~S_Manufacture();
    E_Manufacturer *manufacturer;
    void fillData();
    QString logoUrl;
    CustomeQlabel *image;

private slots:
    void on_btnMenu_clicked();

    void on_btnSave_clicked();

    void capture();

    void on_btnBack_clicked();

private:
    Ui::Manufacture *ui;
};

#endif // MANUFACTURE_H
