#ifndef E_INVOICE_H
#define E_INVOICE_H

#include "repository.h"

class E_InvoiceDetail;
class E_Invoice : public Repository
{
public:
    E_Invoice();
    E_Invoice *getResultSet();
    QString ivID;
    QString userID;
    QString date;
    QString time;
    double subtotal;
    double tax;
    double discount;
    double total;
    QList<E_InvoiceDetail *> listInvDetail;

    static E_Invoice *getInvoiceByID(QString ID);
    static bool insertInvoice(QHash<QString, QString> invoice);
    static QList<E_Invoice *> getListInvoiceByDate(QString fromDate, QString toDate);
    static QString getMaxID();
};

#endif // E_INVOICE_H
