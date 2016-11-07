#ifndef E_INVOICE_H
#define E_INVOICE_H

#include "repository.h"

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

    static E_Invoice *getInvoiceByID(QString ID);
    static bool insertInvoice(QHash<QString, QString> invoice);
    static QString getMaxID();
};

#endif // E_INVOICE_H
