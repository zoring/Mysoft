#ifndef LOGINDB_H
#define LOGINDB_H
#include "basedb.h"
class LoginDB :BaseDB
{
public:
    LoginDB(MYSQL* coon);
    int IsLogin(string idValue,string PasswordValue);
    bool SightUP(string username, string PasswordValue);
    string LoadUserFriends(int UserId, string Password);
private :
    bool CanSigUP(string username);
};

#endif // LOGINDB_H
