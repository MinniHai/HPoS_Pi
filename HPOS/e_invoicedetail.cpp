#include "e_invoicedetail.h"
#include "e_product.h"

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
    invoiceDetail->product  = E_Product::getProductByID(invoiceDetail->proID);
    return invoiceDetail;
}

E_InvoiceDetail *E_InvoiceDetail::getInvoiceDetailByID(QString ID)
{
    Repository *dtRepo = new E_InvoiceDetail();
    dtRepo->setSelectQuery("*", "InvoiceDetail", "dtID", ID);
    return (E_InvoiceDetail *)dtRepo->getEntityByQuery();
}

 QList<E_InvoiceDetail *> E_InvoiceDetail::getListInvoiceDetailByIvID(QString ivID)
{
    QList<E_InvoiceDetail *> list;
    Repository *dtRepo = new E_InvoiceDetail();
    dtRepo->setSelectQuery("*", "InvoiceDetail", "ivID", ivID);
    foreach (Repository *item, dtRepo->getListEntityByQuery()) {
        E_InvoiceDetail *ivDt= (E_InvoiceDetail*)item;
        list.append(ivDt);
    }
    return list;
}

bool E_InvoiceDetail::insertIvDetail(QHash<QString, QString> invoiceDetail)
{
    Repository *proRepo = new E_InvoiceDetail();
    proRepo->setInsertQuery("InvoiceDetail", invoiceDetail);
    return proRepo->query.exec();
}
