class WeChatConnet;
class NetMsgToShow;
#ifndef WECHATCONTROL_H
#define WECHATCONTROL_H
#include "wechatconnet.h"
#include "logindialog.h"
#include <QObject>



class WeChatControl
{
public:
    WeChatControl();
    void SendMsgToNet(int cmmd,int Userid,int Targetid,string username,string msg);
     bool IsConnet();
    bool CheckUser(const string userID, const string Password);
    bool ResightUser(const string userName, const string Password);
private:
    WeChatConnet *NetWorkConnet;
    NetMsgToShow  *toshow;
    LoginDialog* dlg;



};

#endif // WECHATCONTROL_H
