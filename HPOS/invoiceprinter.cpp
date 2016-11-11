#include "invoiceprinter.h"
#include <qtrpt.h>
#include <QtPrintSupport/QPrinter>
#include <QPrinterInfo>
#include <QVariant>
#include <QDebug>
#include <QTextDocument>


InvoicePrinter::InvoicePrinter()
{
    if(QPrinterInfo::availablePrinters().isEmpty()){
        qDebug() << "not available printer";
    } else {
        foreach (QPrinterInfo item, QPrinterInfo::availablePrinters()) {
            qDebug() << item.printerName();
            if(item.printerName() == "HP-LaserJet-1020") {
                QPrinter printer(item);
                QtRPT *report = new QtRPT();
                report->loadReport(":/Report/demoRP");
                report->setPrinter(&printer);
                report->printExec(true,true,item.printerName());
                qDebug() <<"Print with :"+ item.printerName();
                QTextDocument doc("aaaa");
                doc.print(&printer);
            }
        }
        qDebug() << "defaul :" + QPrinterInfo::defaultPrinterName();
    }
//    printer.setPrinterName("HP-LaserJet-1020");
//    printer.setPageSize(QPrinter::A5);

    //report->setValue(0,"demo",QVariant("day la demo"),0);
    //report->printPDF("/mnt/hgfs/Capstone/HPoS_Pi/HPOS/Report/demo.pdf");


//    printer->setPaperSize(QPrinter::A5);
//    QString a = "abc";
//    qDebug() << printer->printerName();

}
