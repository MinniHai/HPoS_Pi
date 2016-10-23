#include "session.h"
#include <QDebug>

Session *Session::s_instance;
Session *Session::instance()
{
    if(!s_instance)
    {
        s_instance = new Session();
    }
    return s_instance;
}

void Session::setUserSession(E_User *user)
{
    this->user = user;
}

E_User *Session::getUserSession()
{
    return user;
}

Session::Session()
{
    user = new E_User();

}
