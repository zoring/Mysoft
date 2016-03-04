#include "logincontrol.h"

LoginControl::LoginControl()
{
    conn = new ConnetDB();
    conn->Connet();
    Login = new LoginDB(conn->GetMysqlPtr());
}

int  LoginControl::IsLogin(string userName, string Password){

    return Login->IsLogin(userName, Password);
}


bool LoginControl::SightUp(string UserName, string Password){

    return Login->SightUP(UserName, Password) ;
}




vector<boost::shared_ptr<string> >  LoginControl::LoadUserFriends(int UserId){
    return Login->LoadUserFriends(UserId) ;
}
