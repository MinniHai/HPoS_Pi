#include "invreportscreen.h"
#include "ui_invreportscreen.h"
#include <QObjectCleanupHandler>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QHeaderView>
#include <QLineEdit>
#include <QCalendarWidget>

#include <e_invoice.h>
#include <e_invoicedetail.h>
#include <invreport.h>
#include <e_product.h>
#include "e_barcode.h"
#include <qscrollbar.h>
#include "utils.h"
#include <math.h>
#include "s_inventorymanager.h"
#include "s_menu.h"


InvReportScreen *InvReportScreen::s_instance;


InvReportScreen *InvReportScreen::instance()
{
    if(!s_instance)
    {
        s_instance = new InvReportScreen();
    }
    return s_instance;
}


InvReportScreen::InvReportScreen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::InvReportScreen)
{
    ui->setupUi(this);
    tableData = new QTableWidget();

    stackL = new QStackedLayout();

    ui->frameData->setLayout(stackL);
    fillLayout();
}

bool InvReportScreen::eventFilter(QObject *obj, QEvent * event){
    if(obj == dateEditFr->calendarWidget() && event->type() == QEvent::Show){
        QPoint pos = dateEditFr->mapToGlobal(dateEditFr->geometry().bottomLeft());
        dateEditFr->calendarWidget()->window()->move(pos.x()-90,pos.y()-8);
    }
    if(obj == dateEditTo->calendarWidget() && event->type() == QEvent::Show){
        QPoint pos = dateEditTo->mapToGlobal(dateEditTo->geometry().bottomLeft());
        dateEditTo->calendarWidget()->window()->move(pos.x()- 450,pos.y()-8);
    }
    return false;
}

void InvReportScreen::fillLayout(){

    dateEditFr = new QDateEdit(ui->frame);
    dateEditFr->setCalendarPopup(true);
    dateEditFr->setDisplayFormat("yyyy-MM-dd");
    dateEditFr->calendarWidget()->setMinimumDate(QDate(2016,11,01));
    dateEditFr->calendarWidget()->setMaximumDate(QDate::currentDate());
    dateEditFr->calendarWidget()->setSelectedDate(QDate::currentDate());
    dateEditFr->setGeometry(47,0,120,31);
    dateEditFr->calendarWidget()->installEventFilter(this);

    dateEditTo = new QDateEdit(ui->frame);
    dateEditTo->setCalendarPopup(true);
    dateEditTo->setDisplayFormat("yyyy-MM-dd");
    dateEditTo->calendarWidget()->setMinimumDate(QDate(2016,11,01));
    dateEditTo->calendarWidget()->setMaximumDate(QDate::currentDate());
    dateEditTo->calendarWidget()->setSelectedDate(QDate::currentDate());
    dateEditTo->setGeometry(236,0,120,31);
    dateEditTo->calendarWidget()->installEventFilter(this);

    QStringList headers;
    headers << tr("Name")
            << tr("Qty")
            << tr("Revenue")
            << tr("Profit")
            << tr("Rate")
               ;
    tableData->setColumnCount(5);
    tableData->setHorizontalHeaderLabels(headers);
    tableData->setSortingEnabled(true);
    tableData->horizontalHeader()->setVisible(true);
    tableData->setGridStyle(Qt::DashDotLine);
    tableData->horizontalHeader()->setSectionResizeMode (QHeaderView::Fixed);
    tableData->verticalHeader()->setVisible(false);
    tableData->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    tableData->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    tableData->verticalScrollBar()->setStyleSheet(
        "QScrollBar:vertical { width: 15; }");

    QGridLayout *saleActivityGrid = new QGridLayout();
    saleActivityGrid->addWidget(tableData);
    QWidget *saleActivityFrame = new QWidget();
    saleActivityFrame->setLayout(saleActivityGrid);
    saleActivityGrid->setContentsMargins(0,0,0,0);

    QGridLayout *sumaryGrid = new QGridLayout();
    ledGrowthRate = new QLineEdit();
    ledTotalCost  = new QLineEdit();
    ledTotalProfit = new QLineEdit();
    ledTotalRevenue = new QLineEdit();
    ledGrowthRate->setReadOnly(true);
    ledTotalCost->setReadOnly(true);
    ledTotalProfit->setReadOnly(true);
    ledTotalRevenue->setReadOnly( true);

    sumaryGrid->addWidget(new QLabel("Capital"),0,0);
    sumaryGrid->addWidget(ledTotalCost,0,1);
    sumaryGrid->addWidget(new QLabel("Gross Revenue"),1,0);
    sumaryGrid->addWidget(ledTotalRevenue,1,1);
    sumaryGrid->addWidget(new QLabel("Gross Profit"),2,0);
    sumaryGrid->addWidget(ledTotalProfit,2,1);
    sumaryGrid->addWidget(new QLabel("Growth Rate"),3,0);
    sumaryGrid->addWidget(ledGrowthRate,3,1);
    QWidget *sumaryWidget = new QWidget();
    sumaryWidget->setLayout(sumaryGrid);
    stackL->addWidget(saleActivityFrame);
    stackL->addWidget(sumaryWidget);
    ui->frameData->setLayout(stackL);
    connect(ui->cbReportType,SIGNAL(currentIndexChanged(int)),SLOT(setCurrentLayoutStack(int)));
    ui->cbReportType->setCurrentIndex(0);
}

void InvReportScreen::setCurrentLayoutStack(int currentIndex){
    stackL->setCurrentIndex(currentIndex);
    if(currentIndex == 0) {
        loadTableData();
    } else if(currentIndex == 1){
        loadSumaryRP();
    }
}

void InvReportScreen::loadSumaryRP()
{
    ledTotalCost->setText(QString::number(totalCost));
    ledTotalProfit->setText(QString::number(totalProfit));
    ledTotalRevenue->setText(QString::number(totalRevenue));
    ledGrowthRate->setText(QString::number(round(totalProfit*100*1.f/totalRevenue*100*1.f)/100));
}

void InvReportScreen::loadTableData()
{
    getListSaleActivity();
    tableData->clearContents();
    tableData->setRowCount(0);
    if(!listReport.isEmpty()) {
        for(int i = 0; i < listReport.size(); i++)
        {
            tableData->insertRow(i);
            tableData->setItem(i, 0, createTableWidgetItem(listReport[i]->productName));
            tableData->setItem(i, 1, createTableWidgetItem(QString::number(listReport[i]->qty)));
            tableData->setItem(i, 2, createTableWidgetItem(QString::number(listReport[i]->revenue)));
            tableData->setItem(i, 3, createTableWidgetItem(QString::number(listReport[i]->profit)));
            tableData->setItem(i, 4, createTableWidgetItem(QString::number(round(listReport[i]->profit*100*1.f/listReport[i]->revenue*100*1.f)/100)));
        }
    }
}

void InvReportScreen::getListSaleActivity()
{
    bool isExist = false;
    totalCost =0;
    totalRevenue =0;
    totalProfit =0;

    QString fromDate = dateEditFr->text();

    QString toDate = dateEditTo->text();

    QList <E_InvoiceDetail *> listDetail;
    foreach (E_Invoice *item, E_Invoice::getListInvoiceByDate(fromDate,toDate)) {
        listDetail << item->listInvDetail;
    }

    foreach (E_InvoiceDetail *item, listDetail) {
        foreach (invReport *invRP, listReport) {
            if(invRP->productName == item->product->name){
                invRP->qty += item->quantity;
                invRP->cost += item->product->barcode->cost;
                invRP->revenue += item->subtotal;
                invRP->profit += item->subtotal - item->quantity*item->product->barcode->cost;

                isExist = true;
                break;
            }
        }

        if(!isExist) {
            invReport *invRP = new invReport();
            invRP->productName = item->product->name;
            invRP->cost = item->product->barcode->cost;
            invRP->qty = item->quantity;
            invRP->revenue = item->subtotal;
            invRP->profit = item->subtotal - item->quantity*item->product->barcode->cost;
            listReport.append(invRP);
        } else {
            isExist = false;
        }
        totalCost += item->product->barcode->cost;
        totalRevenue += item->subtotal;
        totalProfit += item->subtotal - item->quantity*item->product->barcode->cost;
    }
}

QTableWidgetItem *InvReportScreen::createTableWidgetItem(const QString &text) const
{
    QTableWidgetItem *item = new QTableWidgetItem(text);
    item->setTextAlignment(Qt::AlignCenter);
    return item;
}

void InvReportScreen::resizeEvent(QResizeEvent *)
{
    int width =  480 -15;
    tableData->setColumnWidth(0, width * 3.5 / 15);
    tableData->setColumnWidth(1, width * 1.5 / 15);
    tableData->setColumnWidth(2, width * 4 / 15);
    tableData->setColumnWidth(3, width * 4/ 15);
    tableData->setColumnWidth(4, width * 2/ 15);
}

InvReportScreen::~InvReportScreen()
{
    delete ui;
}


void InvReportScreen::on_btnPrint_clicked()
{

}

void InvReportScreen::on_btnLoad_clicked()
{
    loadTableData();
}

void InvReportScreen::on_btnBack_clicked()
{
    S_InventoryManager::instance()->showFullScreen();
    this->close();
}

void InvReportScreen::on_btnMenu_clicked()
{
    S_Menu::instance()->showFullScreen();
    this->close();
}
