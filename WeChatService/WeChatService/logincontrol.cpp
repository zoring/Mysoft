#include "logincontrol.h"

LoginControl::LoginControl()
{
    conn = new ConnetDB();
    conn->Connet();
    Login = new LoginDB(conn->GetMysqlPtr());
}

bool LoginControl::IsLogin(int id, string Password){
    std::stringstream ss;
    std::string str;
    ss<<id;
    ss>>str;
    return Login->IsLogin(str, Password);
}


bool LoginControl::SightUp(string UserName, string Password){
    return Login->SightUP(UserName, Password) ;
}
