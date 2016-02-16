#ifndef CONNETDB_H
#define CONNETDB_H
#include <iostream>
#include<mysql/mysql.h>
#include <boost/smart_ptr.hpp>
using namespace std;
class ConnetDB
{
public:
    ConnetDB();
    bool Connet();
    MYSQL* GetMysqlPtr();
private:
    boost::shared_ptr<MYSQL> conn;
      char* server ;
      char* user;
      char* password ;
      char* database  ;
};

#endif // CONNETDB_H
