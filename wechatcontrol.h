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

class WeChatControl  : public QObject
{
    Q_OBJECT
public:
    WeChatControl();
    void ReadFriendsMsg(int cmmd,int Userid,int Targetid,string username,char* msg);
    void SendMsgToNet(int cmmd,int Userid,int Targetid,string username,string msg);
     bool IsConnet();
    bool CheckUser(const string userID, const string Password);
    bool ResightUser(const string userName, const string Password);
    void ReadMsgFromNet(int cmmd,int Userid,int Targetid,string username,string msg );
    string GetUserName();
    void PushBackFuntions();
   signals:
    void CheckResultFromService(bool result);

private:
    WeChatConnet *NetWorkConnet;
    NetMsgToShow  *toshow;
    LoginDialog* dlg;
    vector<string>  FriendsMsg;
    PersonData* UserMsg;
    int FriendNumbers;
    void ReadIndivideMsg(int cmmd,int Userid,int Targetid,string username,string msg);
    void ReadResightUser(int cmmd,int Userid,int Targetid,string username,string msg);
    void ReadCheckUser(int cmmd,int Userid,int Targetid,string username,string msg);
    void ReadReadGroundMsg(int cmmd,int Userid,int Targetid,string username,string msg);
    void ReadFuntionMsg(int cmmd,int Userid,int Targetid,string username,string msg);

    vector< boost::function<void (int ,int , int , string, string)> > ReadControlFuntions;


};

#endif // WECHATCONTROL_H
