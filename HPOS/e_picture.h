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
    static bool insertPicture(QHash<QString, QString> picture);
    E_Picture *getResultSet();
    QString picUrl;
    QString proID;
};

#endif // E_PICTURE_H
