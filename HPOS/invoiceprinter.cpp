#include "invoiceprinter.h"
#include "cutereport/reportcore.h"
#include "cutereport/reportinterface.h"
#include "cutereport/reportpreview.h"

using namespace CuteReport;
InvoicePrinter::InvoicePrinter()
{
    CuteReport::ReportCore *reportCode = new CuteReport::ReportCore();
    ReportPreview *preview = new ReportPreview();
}
