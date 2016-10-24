#ifndef S_USERMANAGER_H
#define S_USERMANAGER_H

#include <QDialog>
#include <QList>
#include <QTableWidget>
#include <QTableWidgetItem>

class E_User;
namespace Ui {
    class S_UserManager;
}

class S_UserManager : public QDialog
{
    Q_OBJECT

public:

    explicit S_UserManager(QWidget *parent = 0);
    ~S_UserManager();
    void showScreen();
    QList<E_User *> listUser;
    void resizeEvent(QResizeEvent *event);
    QTableWidgetItem *createTableWidgetItem(const QString &text) const;

private slots:

    void runKeyboard();

    void on_btnMenu_clicked();

    void on_btnSearch_clicked();

    void on_btnNew_clicked();

    void on_btnBack_clicked();

private:
    Ui::S_UserManager *ui;
};

#endif // S_USERMANAGER_H
