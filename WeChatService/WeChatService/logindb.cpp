#include "logindb.h"

LoginDB::LoginDB(MYSQL* coon):BaseDB(coon)
{

}
bool LoginDB::IsLogin(string idValue,string PasswordValue){
    string Msg = " select * from user where id = '" + idValue + " and password  = ' " + PasswordValue + " '" ;
    if (mysql_query(Coon.get(), Msg.data()))
        {

            return true;
        }

        return false;
}


bool LoginDB::CanSigUP(string username){
    cout<< "is here?" ;
     string Msg = " select * from user where username = '" + username + " '" ;
     if (mysql_query(Coon.get(), Msg.data()))
         {

             return false;
         }

         return true;
}

bool LoginDB::SightUP(string Username, string PasswirdValue){
    cout<<"Hello ?";
    if (!CanSigUP(Username))
        return false ;
    cout <<Username<< " "<< PasswirdValue<<endl;
    string Msg = "insert user values ("", "+ Username +" , "+ PasswirdValue + " ) ";
    if (mysql_query(Coon.get(), Msg.data()))
        return false;
    return true ;
}
