#ifndef LOGINDB_H
#define LOGINDB_H
#include "basedb.h"
class LoginDB :BaseDB
{
public:
    LoginDB(MYSQL* coon);
    bool IsLogin(string idValue,string PasswordValue);
    bool SightUP(string username, string PasswordValue);
private :
    bool CanSigUP(string username);
};

#endif // LOGINDB_H
