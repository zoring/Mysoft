//利用宏实现属性set和get
#define GetSetNameOfProperty(type, name, access_permission)\
    access_permission: \
    type m_##name; \
    public: \
    inline void set##name(type v){\
    m_##name = v;\
    }\
    inline type get##name() {\
    return m_##name;\
    }
#ifndef DATABASEMSG_H
#define DATABASEMSG_H
#include <string>
#include<iostream>
using namespace std;
class DataBaseMsg
{
public:
    DataBaseMsg();
    GetSetNameOfProperty(int,SendId,private)
    GetSetNameOfProperty(int, ReviceId,private)
    GetSetNameOfProperty(string, UserName,private)
    GetSetNameOfProperty(string,Msg,private)

};

#endif // DATABASEMSG_H
