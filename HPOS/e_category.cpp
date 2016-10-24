#include "e_category.h"

E_Category::E_Category()
{

}

E_Category *E_Category::getResultSet()
{
    E_Category *category = new E_Category();
    category->categoryName = query.value(query.record().indexOf("ctName")).toString();
    return category;
}

E_Category *E_Category::getCategoryByID(QString ctID)
{
    Repository *cateRepo = new E_Category();
    cateRepo->setSelectQuery("*", "Category", "ctID", ctID);
    return (E_Category *) cateRepo->getEntityByQuery();
}
