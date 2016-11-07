#include "e_invoicedetail.h"

E_InvoiceDetail::E_InvoiceDetail()
{

}

E_InvoiceDetail *E_InvoiceDetail::getResultSet()
{
    E_InvoiceDetail *invoiceDetail = new E_InvoiceDetail();
    invoiceDetail->dtID = query.value(query.record().indexOf("dtID")).toString();
    invoiceDetail->ivID = query.value(query.record().indexOf("ivID")).toString();
    invoiceDetail->quantity = query.value(query.record().indexOf("quantity")).toInt();
    invoiceDetail->proID = query.value(query.record().indexOf("proID")).toString();
    invoiceDetail->subtotal = query.value(query.record().indexOf("subtotal")).toLongLong();
    return invoiceDetail;
}

E_InvoiceDetail *E_InvoiceDetail::getInvoiceDetailByID(QString ID)
{
    Repository *dtRepo = new E_InvoiceDetail();
    dtRepo->setSelectQuery("*", "InvoiceDetail", "dtID", ID);
    return (E_InvoiceDetail *)dtRepo->getEntityByQuery();
}

bool E_InvoiceDetail::insertIvDetail(QHash<QString, QString> invoiceDetail)
{
    Repository *proRepo = new E_InvoiceDetail();
    proRepo->setInsertQuery("InvoiceDetail", invoiceDetail);
    return proRepo->query.exec();
}
