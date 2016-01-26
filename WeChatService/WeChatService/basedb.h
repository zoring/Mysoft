

#ifndef BASEDB_H
#define BASEDB_H
#include <iostream>

using namespace std;
class BaseDB
{
public:
    BaseDB();
    bool Find(string TableName, string key="", string value="", string other="");

    
};

#endif // BASEDB_H
