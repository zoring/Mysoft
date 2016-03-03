#ifndef LOGINCONTROL_H
#define LOGINCONTROL_H
#include "connetdb.h"
#include "logindb.h"
class LoginControl
{
public:
    LoginControl();
    int IsLogin(string userName, string Password);
    bool SightUp(string UserName, string Password);
private:
     ConnetDB* conn;
     LoginDB* Login;
};

#endif // LOGINCONTROL_H
