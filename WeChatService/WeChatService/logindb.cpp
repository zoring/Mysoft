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
