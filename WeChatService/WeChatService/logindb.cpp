#include "logindb.h"
#include <stdlib.h>
#include <iostream>
using namespace std ;
LoginDB::LoginDB(MYSQL* coon):BaseDB(coon)
{

}
int LoginDB::IsLogin(string name,string PasswordValue){
    string Msg = " select id from userid where username = '" + name + "' and password  = '" + PasswordValue + "'" ;
     MYSQL_RES *res;
      MYSQL_ROW row;
    if (mysql_query(Coon.get(), Msg.data()))
        {

            return 0;
        }
    res = mysql_use_result(Coon.get());

    if ((row = mysql_fetch_row(res)) == NULL)
    {    mysql_free_result(res);
        return 0;
    }

    cout<<row[0]<<endl;
    int userId = atoi(row[0]) ;
    mysql_free_result(res);
    return userId;
}


bool LoginDB::CanSigUP(string username){
     string Msg = " select * from userid where username = '" + username + "'" ;
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


string LoginDB::LoadUserFriends(int UserId,string userName, string Password){
    if (! IsLogin( userName, Password))
        return "";
    string Msg = "select user.userd, user.username from user, friends where friends.userid = " +UserId ;
    if (mysql_query(Coon.get(), Msg.data()))
        {

            return false;
        }
    MYSQL_RES *res;
    MYSQL_ROW row;
    res = mysql_use_result(Coon.get());
    string Buffer= "";

    row = mysql_fetch_row(res);
    while( row!= NULL)
    {
        cout<<"fdf"<<endl;
    }

}
