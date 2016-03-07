#include "netmsgtoshow.h"
#include "wechatcontrol.h"
#include <boost/bind.hpp>
#include "personlist.h"

#include <iostream>

NetMsgToShow::NetMsgToShow(WeChatControl *WeCtrol):WeCtrol(WeCtrol)
{
     ad = new PersonList(this);


}

void NetMsgToShow::ReviceMsg(int PersonId,string msg){

}

bool NetMsgToShow::SendMsg(const int ReviceId, const string msg){
    WeCtrol->SendMsgToNet(2,0,ReviceId,"",msg);
//     boost::bind(&WeChatControl::SendMsgToNet,WeCtrol,123,msg );

}


void NetMsgToShow::LoginShow(){

 // ad->StaticMainWindow();
int k=9;
 emit NetMsgToShow::StattionFriends(k);

}


void NetMsgToShow::LoadFriendMsg(vector<string> Msg){
    emit FriendsMsgFeomService( Msg);

}

void NetMsgToShow::ChatMegFromNetWork(int TargetId, string Msg){
    emit NetMsgToShow::ChatMsgFromNet(TargetId,Msg);
}
