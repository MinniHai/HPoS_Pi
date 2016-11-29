#include "e_invoice.h"
#include "e_invoicedetail.h"

E_Invoice::E_Invoice()
{

}

E_Invoice *E_Invoice::getResultSet()
{
    E_Invoice *invoice = new E_Invoice();
    invoice->ivID = query.value(query.record().indexOf("ivID")).toString();
    invoice->userID = query.value(query.record().indexOf("userID")).toString();
    invoice->date = query.value(query.record().indexOf("ivDate")).toString();
    invoice->time = query.value(query.record().indexOf("ivTime")).toString();
    invoice->subtotal = query.value(query.record().indexOf("subtotal")).toDouble();
    invoice->tax = query.value(query.record().indexOf("tax")).toDouble();
    invoice->discount = query.value(query.record().indexOf("discount")).toDouble();
    invoice->total = query.value(query.record().indexOf("total")).toDouble();
    invoice->listInvDetail = E_InvoiceDetail::getListInvoiceDetailByIvID(invoice->ivID);
    return invoice;
}

E_Invoice *E_Invoice::getInvoiceByID(QString ID)
{
    Repository *ivRepo = new E_Invoice();
    ivRepo->setSelectQuery("*", "Invoice", "ivID", ID);
    return (E_Invoice *)ivRepo->getEntityByQuery();
}

QList<E_Invoice *> E_Invoice::getListInvoiceByDate(QString fromDate, QString toDate)
{
    QList<E_Invoice *> list;
    Repository *ivRepo = new E_Invoice();
    ivRepo->setSelectQueryFromTo("*", "Invoice", "ivDate",fromDate,toDate);
    foreach (Repository *item, ivRepo->getListEntityByQuery()) {
        E_Invoice *inv = (E_Invoice *)item;
        list.append(inv);
    }
    return list;
}

bool E_Invoice::insertInvoice(QHash<QString, QString> invoice)
{
    Repository *invoiceRepo = new E_Invoice();
    invoiceRepo->setInsertQuery("Invoice", invoice);
    return invoiceRepo->query.exec();
}


QString E_Invoice::getMaxID()
{
    Repository *repository = new E_Invoice();
    repository->setSelectQuery("MAX(ivID)", "Invoice");
    if(repository->query.exec())
    {
        if(repository->query.next())
        {
            return repository->query.value(repository->query.record().indexOf("MAX(ivID)")).toString();
        }
    }
    return "";
}
