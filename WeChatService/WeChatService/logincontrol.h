#ifndef LOGINCONTROL_H
#define LOGINCONTROL_H
#include "connetdb.h"
#include "logindb.h"
#include <vector>
#include<boost/smart_ptr.hpp>
class LoginControl
{
public:
    LoginControl();
    int IsLogin(string userName, string Password);
    bool SightUp(string UserName, string Password);
    vector<boost::shared_ptr<string> > LoadUserFriends(int UserId);
private:

     ConnetDB* conn;
     LoginDB* Login;
};

#endif // LOGINCONTROL_H
