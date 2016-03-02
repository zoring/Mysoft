#include "netmsgtoshow.h"
#include "wechatcontrol.h"
#include <boost/bind.hpp>
#include "personlist.h"
#include <iostream>
NetMsgToShow::NetMsgToShow(WeChatControl *WeCtrol):WeCtrol(WeCtrol)
{    cout<<"fdsf"<<endl;
     ad = new PersonList(this);

}

void NetMsgToShow::ReviceMsg(int PersonId,string msg){

}

bool NetMsgToShow::SendMsg(const int ReviceId, const string msg){
    WeCtrol->SendMsgToNet(3,0,ReviceId,"",msg);
//     boost::bind(&WeChatControl::SendMsgToNet,WeCtrol,123,msg );

}


void NetMsgToShow::LoginShow(){
cout<<"dfdsf"<<endl;
 // ad->StaticMainWindow();
  ad->show();
}
