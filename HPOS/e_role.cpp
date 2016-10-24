#include "e_role.h"
#include <QSqlRecord>
#include <QVariant>

E_Role::E_Role()
{


}
E_Role *E_Role::getResultSet()
{
    E_Role *role = new E_Role();
    role->roleType = query.value(query.record().indexOf("roleType")).toString();
    return role;

}
E_Role *E_Role::getRoleByID(QString id)
{
    Repository *role = new E_Role();
    role->setSelectQuery("*", "Role", "roleID", id);
    return (E_Role *) role->getEntityByQuery();
}
