#ifndef INVREPORT_H
#define INVREPORT_H
#include <QString>

class invReport
{
public:
    invReport();
    QString productName;
    ulong cost;
    ulong revenue;
    ulong profit;
    int qty;
};

#endif // INVREPORT_H
