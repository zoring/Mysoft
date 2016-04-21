#include "basedb.h"

BaseDB::BaseDB(MYSQL* coon)
{
    Coon.reset(coon);
}


//find the message
string BaseDB::FindMsg(string Table, string name,string key, string value, string other){
    string Msg = " select " + name + " from "+ Table +" where "+ key +" = '" + value + " '"+ other;
    string SearMsg = "" ;
    if (mysql_query(Coon.get(), Msg.data()))
        {
            cout<<mysql_error(Coon.get());
            return "";
        }
        res = mysql_use_result(Coon.get());

        while ((row = mysql_fetch_row(res)) != NULL)
        {
           for (int i = 0; i< mysql_num_fields(res);i++)
            SearMsg += row[i];
        }

        mysql_free_result(res);
        return SearMsg;
}


//
bool BaseDB::UpDateMsg(string Tab, string key, string value, string other){

}


bool BaseDB::IsExit(string Tab, string key, string value){
    string Msg = "select * from " + Tab + " where " + key + " = " + value;
    if (mysql_query(Coon.get(), Msg.data()))
        {

            return false;
        }
    MYSQL_RES *res;
    MYSQL_ROW row;
     res = mysql_use_result(Coon.get());
     if ((row = mysql_fetch_row(res)) != NULL)
     {    mysql_free_result(res);
         return true;
     }

     mysql_free_result(res);
        return false;
}

string BaseDB::IntToString(int number){
    std::stringstream ss;
    ss << number;
    std::string str = ss.str();
    return str;
}


vector<string> BaseDB::ReturnGroundBySqlstring(string sqlstatement){
     vector< string> Buffer;
     string buffer;
     if (mysql_query(Coon.get(), sqlstatement.data()))
         {

             return Buffer ;
         }
     MYSQL_RES *res;
     MYSQL_ROW row;
     res = mysql_use_result(Coon.get());


     while ((row = mysql_fetch_row(res)) != NULL)
     {
          for (int i = 0; i< mysql_num_fields(res);i++)
          {

             buffer = row[i];
              Buffer.push_back(buffer);

          }

     }

     mysql_free_result(res);
     return Buffer;
}
