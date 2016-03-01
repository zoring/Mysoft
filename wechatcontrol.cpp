#include "wechatcontrol.h"
#include "wechatconnet.h"
#include <boost/bind.hpp>
#include "netmsgtoshow.h"
#include <iostream>
#include "chatbuffer.h"
using namespace std;
WeChatControl::WeChatControl()
{
    NetWorkConnet = new WeChatConnet();
    dlg= new LoginDialog(this);
    dlg->show();
    //toshow = new NetMsgToShow(this);
}


void WeChatControl::SendMsgToNet( int cmmd,int Userid,int Targetid,string username,string msg){
   ChatBuffer sendMsg;
   if (cmmd >99 || Userid >=10000 || Targetid >=10000|| username.size() >=10 || msg.size() >= 1004)
       return ;
   cout<<cmmd << " "<<Userid<< " "<<Targetid<<" "<< " "<<username<<" "<<msg<<endl;
   sendMsg.SetCmmd(cmmd);
   sendMsg.SetUserId(Userid);
   sendMsg.SetTargetId(Targetid);
   sendMsg.SetName(username);
   sendMsg.SetBody(msg);

   cout<<sendMsg.GetBody()<<endl;
   cout<<"endl"<<endl;
    NetWorkConnet->SendIndividualMsg(string(sendMsg.data(),1024));
//    boost::bind(&WeChatConnet::SendIndividualMsg,NetWorkConnet,msg);
}

bool WeChatControl::IsConnet(){

    if (dlg->GetIsLogin())
    {toshow = new NetMsgToShow(this);
    return true;
    }
    return false;
}


bool WeChatControl::CheckUser( string userName,  string Password){

    SendMsgToNet(1,0,0,userName,Password);
    return true;
}


bool WeChatControl::ResightUser(const string userName, const string Password){

     SendMsgToNet(0,0,0,userName,Password);
}
