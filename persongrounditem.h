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

#ifndef PERSONGROUNDITEM_H
#define PERSONGROUNDITEM_H
#include <QListWidgetItem>
#include <QListWidget>
#include <list>
#include "personlist.h"
#include "person.h"

using namespace std;
class PersonGroundItem: public QListWidgetItem
{
public:
    PersonGroundItem(const QString GroundName, QListWidget* itemlist);

public:
    void AddPerson(Person const Personid);
    void DelPerson(Person const Personid);
    bool operator ==(PersonGroundItem other);
    list<Person>& getPersonList();
    int getgroundId();
private:
    int GroundId;
    std::list<Person> personlist;



GetSetNameOfProperty (std::string, GroundName, private)
GetSetNameOfProperty (std::string, ImageUrl, private)
GetSetNameOfProperty(bool,IsHidden,private)

};
#endif // PERSONGROUNDITEM_H



