#ifndef E_STATE_H
#define E_STATE_H
#include "repository.h"
#include <QString>
#include <QList>

class E_State : public Repository
{
public:
    E_State();
    E_State *getResultSet();
    QString stateID;
    QString state;
    QString des;

    static E_State *getStateByID(QString stateID);
    static QList<E_State *> getAllState();

};

#endif // E_STATE_H
