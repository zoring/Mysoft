#include "logincontrol.h"

LoginControl::LoginControl()
{
    conn = new ConnetDB();
    conn->Connet();
    Login = new LoginDB(conn->GetMysqlPtr());
}

bool LoginControl::IsLogin(string name,string value,string password,string PasswordValue){
    return Login->IsLogin(name,value,password,PasswordValue);
}
