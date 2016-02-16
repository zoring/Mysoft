#ifndef LOGINCONTROL_H
#define LOGINCONTROL_H
#include "connetdb.h"
#include "logindb.h"
class LoginControl
{
public:
    LoginControl();
    bool IsLogin(string name,string value,string password,string PasswordValue);
private:
     ConnetDB* conn;
     LoginDB* Login;
};

#endif // LOGINCONTROL_H
