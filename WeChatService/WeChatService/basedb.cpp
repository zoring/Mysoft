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


string BaseDB::IntToString(int number){
    std::stringstream ss;
    ss << number;
    std::string str = ss.str();
    return str;
}
