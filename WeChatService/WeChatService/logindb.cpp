#include "logindb.h"

LoginDB::LoginDB(MYSQL* coon):BaseDB(coon)
{

}
bool LoginDB::IsLogin(string idValue,string PasswordValue){
    string Msg = " select * from user where id = '" + idValue + "' and password  = '" + PasswordValue + "'" ;
     MYSQL_RES *res;
      MYSQL_ROW row;
    if (mysql_query(Coon.get(), Msg.data()))
        {

            return false;
        }
    res = mysql_use_result(Coon.get());
    if ((row = mysql_fetch_row(res)) == NULL)
    {    mysql_free_result(res);
        return false;
    }
    mysql_free_result(res);
    return true;
}


bool LoginDB::CanSigUP(string username){
     string Msg = " select * from user where name = '" + username + "'" ;
     cout<<Msg<<endl;
     if (mysql_query(Coon.get(), Msg.data()))
         {

             return false;
         }
     MYSQL_RES *res;
     MYSQL_ROW row;
      res = mysql_use_result(Coon.get());
      if ((row = mysql_fetch_row(res)) != NULL)
      {    mysql_free_result(res);
          return false;
      }

      mysql_free_result(res);
         return true;
}

bool LoginDB::SightUP(string Username, string PasswirdValue){
    if (!CanSigUP(Username))
        return false ;
    string Msg = "insert user values (null,'"+ Username +"' , '"+ PasswirdValue + "'); ";
    cout<<Msg<<endl;
    if (mysql_query(Coon.get(), Msg.data()))
        return false;
    return true ;
}
