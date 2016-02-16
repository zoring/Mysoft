#ifndef DBCONTROL_H
#define DBCONTROL_H
#include <iostream>
#include<mysql/mysql.h>
#include <boost/smart_ptr.hpp>
#include "connetdb.h"


class DBControl
{
public:
    DBControl();
    bool connet();
    string SearService();
    bool UpdateService();
    bool DeleteService();
    bool InsertService();
private:
    ConnetDB* conn;

};

#endif // DBCONTROL_H
