#ifndef SESSION_H
#define SESSION_H

#include "e_user.h"
class Session
{
public:
    static Session *s_instance;
    static Session *instance();
    void setUserSession(E_User *user);
    E_User *getUserSession();
    ~Session();

private:
    Session();
    E_User *user;
};

#endif // SESSION_H
