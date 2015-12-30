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

#ifndef PERSON_H
#define PERSON_H
#include <string>

class Person
{
public:
    Person();
   bool operator== (Person other);
   int getPersonId();
private:
   int Personid;
  GetSetNameOfProperty(std::string, PersonName, private)
  GetSetNameOfProperty(std::string, SigWord, private)
  GetSetNameOfProperty(std::string, ImageUrl, private)
  GetSetNameOfProperty(bool,isOnline,private)
};

#endif // PERSON_H
