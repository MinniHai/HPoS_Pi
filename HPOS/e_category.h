#ifndef E_CATAGORY_H
#define E_CATAGORY_H

#include "repository.h"

class E_Category : public Repository
{
public:
    E_Category();
    QString categoryName;

    E_Category *getResultSet();
    static E_Category *getCategoryByID(QString ctID);

};

#endif // E_CATAGORY_H
