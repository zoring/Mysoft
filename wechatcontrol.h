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
    void SendMsgToNet(int Userid,string msg);

private:
    WeChatConnet *NetWorkConnet;
    NetMsgToShow  *toshow;


};

#endif // WECHATCONTROL_H
