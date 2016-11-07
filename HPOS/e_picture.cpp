#include "e_picture.h"
#include "utils.h"

E_Picture::E_Picture()
{

}

E_Picture *E_Picture::getResultSet()
{
    E_Picture *picture = new E_Picture();
    picture->picUrl = query.value(query.record().indexOf("picUrl")).toString();
    picture->proID = query.value(query.record().indexOf("proID")).toString();
    return picture;
}

QList<E_Picture *> E_Picture::getPictureByProductID(QString ID)
{
    QList<E_Picture *> listPicture ;
    Repository *pictureRepo = new E_Picture();
    pictureRepo->setSelectQuery("*", "Picture", "proID", ID);
    foreach(Repository *item, pictureRepo->getListEntityByQuery())
    {
        listPicture.append((E_Picture *)item);
    }
    return listPicture;
}

bool E_Picture::insertPicture(QHash<QString, QString> picture)
{
    Repository *picRepo = new E_Picture();
    picRepo->setInsertQuery("Picture", picture);
    return picRepo->query.exec();
}
