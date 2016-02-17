#include "wechatcontrol.h"
#include "wechatconnet.h"
#include <boost/bind.hpp>
#include "netmsgtoshow.h"
#include <iostream>
using namespace std;
WeChatControl::WeChatControl()
{
    NetWorkConnet = new WeChatConnet();
    dlg= new LoginDialog(this);
    dlg->show();
    //toshow = new NetMsgToShow(this);
}

void WeChatControl::SendMsgToNet( int comment = 123, string msg=""){
    std::stringstream ss;
    std::string str;
    ss<<comment;
    ss>>str;
    str += ":" ;
    msg=str+msg;
    cout<<msg<<endl;
    NetWorkConnet->SendIndividualMsg(msg);
//    boost::bind(&WeChatConnet::SendIndividualMsg,NetWorkConnet,msg);
}

bool WeChatControl::IsConnet(){

    if (dlg->GetIsLogin())
    {toshow = new NetMsgToShow(this);
    return true;
    }
    return false;
}


bool WeChatControl::CheckUser( string userID,  string Password){
    userID = userID + ":" +Password ;
    cout<<userID<<endl;
    SendMsgToNet(20,userID);
    return true;
}
