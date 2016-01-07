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
#ifndef PERSONDATA_H
#define PERSONDATA_H

#include <QWidget>

class PersonData
{
public:
    PersonData();

};

#endif // PERSONDATA_H
