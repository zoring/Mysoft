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
    bool SendMsg(const int ReviceId, const string msg);
    void LoginShow();
    void LoadFriendMsg(vector<string> Msg);
    string GetUserName();
    void ChatMegFromNetWork(int TargetId, string Msg,string UserName);
signals:
    void ChatMsgFromNet(int TargetId,string Msg,string UserName);
    void StattionFriends(int number);
    void FriendsMsgFeomService(vector<string> Msg);

private :
    WeChatControl   *WeCtrol;
    PersonList* ad;
    PersonData* UserMsg;

};

#endif // NETMSGTOSHOW_H
