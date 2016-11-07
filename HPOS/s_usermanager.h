#ifndef S_USERMANAGER_H
#define S_USERMANAGER_H

#include <QDialog>
#include <QList>
#include <QTableWidget>
#include <QTableWidgetItem>

class E_User;
class E_State;

namespace Ui {
    class S_UserManager;
}

class S_UserManager : public QDialog
{
    Q_OBJECT

public:
    static S_UserManager *s_instance;
    static S_UserManager *instance();

    explicit S_UserManager(QWidget *parent = 0);
    ~S_UserManager();
    void setDataToTable();
    QList<E_User *> listUser;
    void resizeEvent(QResizeEvent *);
    QTableWidgetItem *createTableWidgetItem(const QString &text) const;

private slots:

    void search();

    void runKeyboard();

    void on_btnMenu_clicked();

    void on_btnNew_clicked();

    void on_btnBack_clicked();

    void on_btnDelete_clicked();

    void edit_clicked(int row);

    void cell_click(int row, int column);

private:
    QList<E_State *> listState;
    Ui::S_UserManager *ui;
};

#endif // S_USERMANAGER_H
