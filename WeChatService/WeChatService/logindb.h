#ifndef LOGINDB_H
#define LOGINDB_H
#include "basedb.h"
#include <vector>
#include<boost/smart_ptr.hpp>
class LoginDB :BaseDB
{
public:
    LoginDB(MYSQL* coon);
    int IsLogin(string idValue,string PasswordValue);
    bool SightUP(string username, string PasswordValue);
    vector<boost::shared_ptr<string> > LoadUserFriends(int UserId,int groundsid);
    vector<boost::shared_ptr<string> > LoadGroundMsg(int UserId);


private :
    bool CanSigUP(string username);
};

#endif // LOGINDB_H
