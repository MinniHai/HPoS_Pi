#ifndef E_INVOICEDETAIL_H
#define E_INVOICEDETAIL_H

#include "repository.h"
class E_InvoiceDetail : public Repository
{
public:
    E_InvoiceDetail();
    E_InvoiceDetail *getResultSet();
    QString dtID;
    QString ivID;
    QString proID;
    int quantity;
    ulong subtotal;

    static E_InvoiceDetail *getInvoiceDetailByID(QString ID);
    static bool insertIvDetail(QHash<QString, QString> invoiceDetail);
};

#endif // E_INVOICEDETAIL_H
