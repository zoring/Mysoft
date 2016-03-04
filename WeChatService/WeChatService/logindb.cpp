#include "logindb.h"
#include <stdlib.h>
#include <iostream>
using namespace std ;
LoginDB::LoginDB(MYSQL* coon):BaseDB(coon)
{

}
int LoginDB::IsLogin(string name,string PasswordValue){
    string Msg = " select userid from user where username = '" + name + "' and password  = '" + PasswordValue + "'" ;
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

    int userId = atoi(row[0]) ;
    mysql_free_result(res);
    return userId;
}


bool LoginDB::CanSigUP(string username){
     string Msg = " select * from user where username = '" + username + "'" ;
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


vector<boost::shared_ptr<string> > LoginDB::LoadUserFriends(int UserId){
      vector< boost::shared_ptr<string> > friendsBuffer;

    string Msg = " select user.userid, user.username from user, friends where friends.userid = " + IntToString(UserId) ;
    Msg += " and  friends.friendid = user.userid";
    if (mysql_query(Coon.get(), Msg.data()))
        {

            return friendsBuffer ;
        }
    MYSQL_RES *res;
    MYSQL_ROW row;
    res = mysql_use_result(Coon.get());


    while ((row = mysql_fetch_row(res)) != NULL)
    {	boost::shared_ptr<string> buffer(new string(""));
         for (int i = 0; i< mysql_num_fields(res);i++)
         {
            *(buffer.get()) += row[i];


         }
         friendsBuffer.push_back(buffer);
    }

    mysql_free_result(res);
    return friendsBuffer;
}
