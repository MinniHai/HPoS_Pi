#ifndef E_ROLE_H
#define E_ROLE_H
#include "repository.h"


class E_Role: public Repository
{
public:
    E_Role();
    E_Role *getResultSet();
    QString roleType;
    E_Role *getRoleByID(QString ID);
};

#endif // E_ROLE_H
