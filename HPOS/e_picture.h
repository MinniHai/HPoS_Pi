#ifndef E_PICTURE_H
#define E_PICTURE_H
#include <QString>
#include <QList>
#include "repository.h"
class E_Picture : public Repository
{
public:
    E_Picture();
    static QList<E_Picture *> getPictureByProductID(QString ID);
    E_Picture *getResultSet();
    QString picUrl;
};

#endif // E_PICTURE_H
