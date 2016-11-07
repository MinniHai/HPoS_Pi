#include "e_state.h"


E_State::E_State()
{

}

E_State *E_State::getResultSet()
{
    E_State *state = new E_State();
    state->stateID = query.value(query.record().indexOf("stateID")).toString();
    state->state = query.value(query.record().indexOf("state")).toString();
    state->des = query.value(query.record().indexOf("description")).toString();
    return state;
}

E_State *E_State::getStateByID(QString stateID)
{
    Repository *stateRepo = new E_State();
    stateRepo->setSelectQuery("*", "State", "stateID", stateID);
    return (E_State *)stateRepo->getEntityByQuery();
}

QList<E_State *> E_State::getAllState()
{
    QList <E_State *> listState;

    Repository *stateRepo = new E_State();
    stateRepo->setSelectQuery("*", "State");
    foreach(Repository *item, stateRepo->getListEntityByQuery())
    {
        listState.append((E_State *)item);
    }
    return listState;
}
