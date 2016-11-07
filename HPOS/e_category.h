#ifndef E_CATAGORY_H
#define E_CATAGORY_H

#include "repository.h"

class E_Category : public Repository
{
public:
    E_Category();
    QString categoryName;
    QString ctID;

    E_Category *getResultSet();
    static E_Category *getCategoryByID(QString ctID);
    static QList<E_Category *> searchCategoryByName(QString Name);
    static QList<E_Category *> getAllCategory();

};

#endif // E_CATAGORY_H
