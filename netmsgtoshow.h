class WeChatControl;
class PersonList;
#ifndef NETMSGTOSHOW_H
#define NETMSGTOSHOW_H
#include <boost/smart_ptr.hpp>
#include <string>
#include <map>
using namespace std;

class NetMsgToShow
{
public:
    NetMsgToShow(WeChatControl *WeCtrol);
    void ReviceMsg(int PersonId,string msg);
    bool SendMsg(int ReviceId, string mag);
    void LoginShow();
private :
    WeChatControl   *WeCtrol;
    PersonList* ad;

};

#endif // NETMSGTOSHOW_H
