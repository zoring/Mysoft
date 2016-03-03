class WeChatConnet;
class NetMsgToShow;
#ifndef WECHATCONTROL_H
#define WECHATCONTROL_H
#include "wechatconnet.h"
#include "logindialog.h"
#include <QObject>
#include <boost/function.hpp>


class WeChatControl  : public QObject
{
    Q_OBJECT
public:
    WeChatControl();
    void SendMsgToNet(int cmmd,int Userid,int Targetid,string username,string msg);
     bool IsConnet();
    bool CheckUser(const string userID, const string Password);
    bool ResightUser(const string userName, const string Password);
    void ReadMsgFromNet(int cmmd,int Userid,int Targetid,string username,string msg );
    void PushBackFuntions();
   signals:
    void CheckResultFromService(bool result);


private:
    WeChatConnet *NetWorkConnet;
    NetMsgToShow  *toshow;
    LoginDialog* dlg;
    void ReadIndivideMsg(int cmmd,int Userid,int Targetid,string username,string msg);
    void ReadResightUser(int cmmd,int Userid,int Targetid,string username,string msg);
    void ReadCheckUser(int cmmd,int Userid,int Targetid,string username,string msg);
    void ReadReadGroundMsg(int cmmd,int Userid,int Targetid,string username,string msg);
    void ReadFuntionMsg(int cmmd,int Userid,int Targetid,string username,string msg);

    vector< boost::function<void (int ,int , int , string, string)> > ReadControlFuntions;


};

#endif // WECHATCONTROL_H
