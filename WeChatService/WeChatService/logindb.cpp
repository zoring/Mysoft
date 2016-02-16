#include "logindb.h"

LoginDB::LoginDB(MYSQL* coon):BaseDB(coon)
{

}
bool LoginDB::IsLogin(string id,string value,string password,string PasswordValue){
    string Msg = " select * from user where "+ id +" = '" + value + " ' "+ " and " +password + " = ' " + PasswordValue + " '" ;
    if (mysql_query(Coon.get(), Msg.data()))
        {

            return false;
        }

        return true;
}
