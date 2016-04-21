class WeChatConnet;
class NetMsgToShow;
class PersonData;
#ifndef WECHATCONTROL_H
#define WECHATCONTROL_H
#include "wechatconnet.h"
#include "logindialog.h"
#include <QObject>
#include <boost/function.hpp>
#include <vector>
#include <set>
#include "elumdata.h"
class WeChatControl  : public QObject
{
    Q_OBJECT
public:
    typedef boost::function<void (int ,int , int , string, char*)> ReadFuntion2;
    WeChatControl();
    void PushBackFuntions();
    void SendMsgToNet(int cmmd,int Userid,int Targetid,string username,string msg);
     bool IsConnet();
    bool CheckUser(const string userID, const string Password);
    bool ResightUser(const string userName, const string Password);
    void ReadMsgFromNet(int cmmd,int Userid,int Targetid,string username,string msg );
    string GetUserName();
    void ReadMsgFromNetByChar(int cmmd,int Userid,int Targetid,string username,char* msg);
   signals:
    void CheckResultFromService(bool result);

private:
    WeChatConnet *NetWorkConnet;
    NetMsgToShow  *toshow;
    LoginDialog* dlg;
    vector<string>  FriendsGroundMsg;
    vector<string>  FoundFriends;
    PersonData* UserMsg;
    set<int> HasReadGrounds;
    map<int,vector<string> > groundMapFriend;
    int FriendGroundsNumbers;

    void PushBackFunByChar();
    void ReadIndivideMsg(int cmmd,int Userid,int Targetid,string username,string msg);
    void ReadResightUser(int cmmd,int Userid,int Targetid,string username,string msg);
    void ReadCheckUser(int cmmd,int Userid,int Targetid,string username,string msg);
    void ReadReadGroundMsg(int cmmd,int Userid,int Targetid,string username,string msg);
    void ReadFuntionMsg(int cmmd,int Userid,int Targetid,string username,string msg);
   void ReadAddGround(int cmmd,int Userid,int Targetid,string username,string msg);
    ElumData elumdata;
    vector< boost::function<void (int ,int , int , string, string)> > ReadControlFuntions;

    void ReadGroundMsg(int cmmd,int Userid,int Targetid,string username,char* msg);
     void ReadFoundFriendResult(int cmmd,int Userid,int Targetid,string username,char* msg);
     void ReadFriendsMsg(int cmmd,int Userid,int Targetid,string username,char* msg);
    map<int,ReadFuntion2> readFunFromNet;
};

#endif // WECHATCONTROL_H
