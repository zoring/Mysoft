#include "connetdb.h"

ConnetDB::ConnetDB()
{
    server = "localhost";
     user = "root";
     password = "beingdone";
     database = "WeChat";
     conn.reset(mysql_init(NULL));
}


bool ConnetDB::Connet(){
    if (!mysql_real_connect(conn.get(), server,user, password, database, 0, NULL, 0))
      {

      cout<<mysql_error(conn.get());
          return false;
      }
    return true;
}

MYSQL* ConnetDB::GetMysqlPtr(){
    return conn.get();
}
