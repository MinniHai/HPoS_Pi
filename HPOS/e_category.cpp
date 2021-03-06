#include "e_category.h"

E_Category::E_Category()
{

}

E_Category *E_Category::getResultSet()
{
    E_Category *category = new E_Category();
    category->ctID = query.value(query.record().indexOf("ctID")).toString();
    category->categoryName = query.value(query.record().indexOf("ctName")).toString();
    return category;
}

E_Category *E_Category:: getCategoryByID(QString ctID)
{
    Repository *cateRepo = new E_Category();
    cateRepo->setSelectQuery("*", "Category", "ctID", ctID);
    return (E_Category *) cateRepo->getEntityByQuery();
}

QList<E_Category *> E_Category::searchCategoryByName(QString Name)
{
    QList<E_Category *> listCategory;
    Repository *cateRepo = new E_Category();
    cateRepo->setSelectLikeQuery("*", "Category", "ctName", Name);
    foreach(Repository *item, cateRepo->getListEntityByQuery())
    {
        listCategory.append((E_Category *)item);
    }
    return listCategory;
}

QList<E_Category *> E_Category::getAllCategory()
{
    QList<E_Category *> listCategory;
    Repository *cateRepo = new E_Category();
    cateRepo->setSelectQuery("*", "Category");
    foreach(Repository *item, cateRepo->getListEntityByQuery())
    {
        listCategory.append((E_Category *)item);
    }
    return listCategory;
}
