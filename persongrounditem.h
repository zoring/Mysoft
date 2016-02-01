class NetMsgToShow;
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

#include <QListWidget>
#include <list>
#include "person.h"
#include "QLabel"
using namespace std;
class PersonGroundItem: public QWidget
{

public:
      PersonGroundItem(NetMsgToShow* NetToShow,int UserId, char* UesrName, char* SiginWord, char* IamgeUrl="",QWidget *parent=0);

public:
    void AddPerson(Person const Personid);
    void DelPerson(Person const Personid);
    bool operator ==(const PersonGroundItem& other);
    list<Person>& getPersonList();
    int getgroundId() const;
    bool eventFilter(QObject *obj, QEvent *event);//事件过滤器

    protected:
    void mouseDoubleClickEvent (QMouseEvent *event);
private:
    int UserId;
    std::list<Person> personlist;
    QLabel *UserName;  //用户名
    QLabel *SiginWord;  //个性签名
    QWidget *PersonImage;//用户头像
    string ImageUrl;
    NetMsgToShow *NetToShow;
GetSetNameOfProperty (std::string, IPAddress, private)
GetSetNameOfProperty (std::string, GroundName, private)
GetSetNameOfProperty (std::string, ImageUrl, private)
GetSetNameOfProperty(bool,IsHidden,private)

};
#endif // PERSONGROUNDITEM_H



