#ifndef LOGINDB_H
#define LOGINDB_H
#include "basedb.h"
class LoginDB :BaseDB
{
public:
    LoginDB(MYSQL* coon);
    bool IsLogin(string name,string value,string password,string PasswordValue);
};

#endif // LOGINDB_H
