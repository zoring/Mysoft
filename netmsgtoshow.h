class WeChatControl;
class PersonList;
#ifndef NETMSGTOSHOW_H
#define NETMSGTOSHOW_H
#include <boost/smart_ptr.hpp>
#include <string>
#include <map>
#include <QObject>
using namespace std;

class NetMsgToShow : public QObject
{
    Q_OBJECT
public:
    NetMsgToShow(WeChatControl *WeCtrol);
    void ReviceMsg(int PersonId,string msg);
    bool SendMsg(int ReviceId, string mag);
    void LoginShow();
signals:
    void StattionFriends(int number);
private :
    WeChatControl   *WeCtrol;
    PersonList* ad;

};

#endif // NETMSGTOSHOW_H
