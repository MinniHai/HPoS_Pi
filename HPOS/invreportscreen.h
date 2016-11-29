#ifndef INVREPORTSCREEN_H
#define INVREPORTSCREEN_H

#include <QDialog>
#include <QLabel>
#include <QGridLayout>
#include <QStackedLayout>
#include <QTableWidget>
#include <QFrame>
#include <QList>
#include <QDateEdit>

class E_Invoice;
class invReport;
namespace Ui {
class InvReportScreen;
}

class InvReportScreen : public QDialog
{
    Q_OBJECT

public:

    static InvReportScreen *s_instance;
    static InvReportScreen *instance();
    explicit InvReportScreen(QWidget *parent = 0);
    ~InvReportScreen();
    void loadTableData();
    void loadSumaryRP();

private slots:
    void on_btnPrint_clicked();
    void setCurrentLayoutStack(int currentIndex);

    void on_btnLoad_clicked();

    void on_btnBack_clicked();

    void on_btnMenu_clicked();

private:
    bool eventFilter(QObject *obj, QEvent *event);
    void getListSaleActivity() ;
    void resizeEvent(QResizeEvent *);
    QTableWidgetItem *createTableWidgetItem(const QString &text) const;
    void fillLayout();

    QDateEdit *dateEditFr;
    QDateEdit *dateEditTo;
    QList<invReport *> listReport;
    QTableWidget *tableData;
    Ui::InvReportScreen *ui;

    QLineEdit *ledTotalCost;
    QLineEdit *ledTotalRevenue;
    QLineEdit *ledTotalProfit;
    QLineEdit *ledGrowthRate;

    ulong totalCost;
    ulong totalRevenue;
    ulong totalProfit;
    ulong growthRate;

    QStackedLayout *stackL;
    QLabel *demo;
};

#endif // INVREPORTSCREEN_H
