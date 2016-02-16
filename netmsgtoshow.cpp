#include "netmsgtoshow.h"
#include "wechatcontrol.h"
#include <boost/bind.hpp>
#include "personlist.h"
#include <iostream>
NetMsgToShow::NetMsgToShow(WeChatControl *WeCtrol):WeCtrol(WeCtrol)
{
     ad = new PersonList(this);
    ad->show();
}

void NetMsgToShow::ReviceMsg(int PersonId,string msg){

}

bool NetMsgToShow::SendMsg(const int ReviceId, const string msg){
    WeCtrol->SendMsgToNet(123,msg);
//     boost::bind(&WeChatControl::SendMsgToNet,WeCtrol,123,msg );

}
