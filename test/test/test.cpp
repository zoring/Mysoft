#include <mysql/mysql.h>
#include <iostream>
#include <boost/smart_ptr.hpp>
using namespace std;
boost::shared_ptr<MYSQL> conn;
int main() 
{
    
    MYSQL_RES *res;
    MYSQL_ROW row;
    char server[] = "localhost";
    char user[] = "root";
    char password[] = "beingdone";
    char database[] = "WeChat";
   // conn = mysql_init(NULL);

     conn.reset(mysql_init(NULL));
    
    if (!mysql_real_connect(conn.get(), server,user, password, database, 0, NULL, 0)) 
    {
        
	cout<<mysql_error(conn.get());
        return 0;
    }
    
 
 
     if (mysql_query(conn.get(), "select id,username from user where username = 'www ' and password = 'www'; ")) 
    {
        cout<<mysql_error(conn.get());
        return 0;
    }
    
     res = mysql_use_result(conn.get());

    while ((row = mysql_fetch_row(res)) != NULL)
    {	
       for (int i = 0; i< mysql_num_fields(res);i++)
       cout<<row[i]<<endl;
        
    }
    
    mysql_free_result(res);
   
    
    return 0;
}
