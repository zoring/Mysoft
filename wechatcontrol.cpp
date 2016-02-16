#include "wechatcontrol.h"
#include "wechatconnet.h"
#include <boost/bind.hpp>
#include "netmsgtoshow.h"
#include <iostream>
using namespace std;
WeChatControl::WeChatControl()
{
    NetWorkConnet = new WeChatConnet();
    dlg= new LoginDialog();
    dlg->show();
    //toshow = new NetMsgToShow(this);
}

void WeChatControl::SendMsgToNet(int Userid = 123, string msg=""){
    std::stringstream ss;
    std::string str;
    ss<<Userid;
    ss>>str;
    str += ":" ;
    msg=str+msg;
    cout<<msg<<endl;
    NetWorkConnet->SendIndividualMsg(msg);
//    boost::bind(&WeChatConnet::SendIndividualMsg,NetWorkConnet,msg);
}

bool WeChatControl::IsConnet(){

}
