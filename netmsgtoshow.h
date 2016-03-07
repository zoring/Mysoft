class WeChatControl;
class PersonList;
class PersonData;
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
    void LoadFriendMsg(vector<string> Msg);
    void ChatMegFromNetWork(int TargetId, string Msg);
signals:
    void StattionFriends(int number);
    void FriendsMsgFeomService(vector<string> Msg);
    void ChatMsgFromNet(int TargetId,string Msg);
private :
    WeChatControl   *WeCtrol;
    PersonList* ad;
    PersonData* UserMsg;

};

#endif // NETMSGTOSHOW_H
