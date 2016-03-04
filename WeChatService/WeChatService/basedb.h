#ifndef BASEDB_H
#define BASEDB_H
#include <iostream>
#include<mysql/mysql.h>
#include <boost/smart_ptr.hpp>
#include <boost/signal.hpp>
using namespace std;
class BaseDB
{
public:
    BaseDB(MYSQL* coon);
    string FindMsg(string Tab,string name,string key,string value,string other= "");
    bool SaveMsg(string Tab,string key,string value,string other);
    bool DeleteMsg(string Tab,string key,string value,string other);
    bool UpDateMsg(string Tab,string key,string value,string other);
    string IntToString(int number);
protected:
    boost::shared_ptr<MYSQL> Coon;
private:
    MYSQL_RES *res;
    MYSQL_ROW row;
};

#endif // BASEDB_H
