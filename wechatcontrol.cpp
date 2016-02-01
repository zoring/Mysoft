#include "wechatcontrol.h"
#include "wechatconnet.h"
#include <boost/bind.hpp>
#include "netmsgtoshow.h"
#include <iostream>
using namespace std;
WeChatControl::WeChatControl()
{
    NetWorkConnet = new WeChatConnet();
    toshow = new NetMsgToShow(this);
}

void WeChatControl::SendMsgToNet(int Userid, string msg){
    cout<<msg<<endl;
    NetWorkConnet->SendIndividualMsg(msg);
//    boost::bind(&WeChatConnet::SendIndividualMsg,NetWorkConnet,msg);
}

