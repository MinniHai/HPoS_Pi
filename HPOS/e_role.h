#ifndef E_ROLE_H
#define E_ROLE_H
#include "repository.h"

class E_Role: public Repository
{
public:
    E_Role();
    E_Role *getResultSet();
    QString roleType;
    QString roleID;
    QList<E_Role *> listRole;
    static E_Role *getRoleByID(QString ID);
    static QList<E_Role *> getAllRole();
};

#endif // E_ROLE_H
