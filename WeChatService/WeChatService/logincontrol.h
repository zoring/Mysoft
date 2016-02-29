#ifndef LOGINCONTROL_H
#define LOGINCONTROL_H
#include "connetdb.h"
#include "logindb.h"
class LoginControl
{
public:
    LoginControl();
    bool IsLogin(int id, string Password);
    bool SightUp(string UserName, string Password);
private:
     ConnetDB* conn;
     LoginDB* Login;
};

#endif // LOGINCONTROL_H
