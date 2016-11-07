#include "e_role.h"
#include <QSqlRecord>
#include <QVariant>
#include <QList>

E_Role::E_Role()
{


}
E_Role *E_Role::getResultSet()
{
    E_Role *role = new E_Role();
    role->roleID = query.value(query.record().indexOf("roleID")).toString();
    role->roleType = query.value(query.record().indexOf("roleType")).toString();
    return role;

}
E_Role *E_Role::getRoleByID(QString id)
{
    Repository *role = new E_Role();
    role->setSelectQuery("*", "Role", "roleID", id);
    return (E_Role *) role->getEntityByQuery();
}
QList<E_Role *> E_Role::getAllRole()
{
    QList <E_Role *> listRole;

    Repository *productRepo = new E_Role();
    productRepo->setSelectQuery("*", "Role");
    foreach(Repository *item, productRepo->getListEntityByQuery())
    {

        listRole.append((E_Role *)item);
    }
    return listRole;
}
