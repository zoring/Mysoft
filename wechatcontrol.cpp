#include "wechatcontrol.h"
#include "wechatconnet.h"
#include <boost/bind.hpp>
#include "netmsgtoshow.h"
#include <iostream>
#include "chatbuffer.h"
#include "persondata.h"
#include "friendsbuffer.h"
using namespace std;
WeChatControl::WeChatControl()
{
    FriendNumbers = 0;
    NetWorkConnet = new WeChatConnet(this);
    dlg= new LoginDialog(this);
    dlg->show();
    toshow = new NetMsgToShow(this);
    UserMsg = new PersonData();
    //toshow = new NetMsgToShow(this);
}


void WeChatControl::SendMsgToNet( int cmmd,int Userid,int Targetid,string username,string msg){
   ChatBuffer sendMsg;
   if (cmmd >99 || Userid >=10000 || Targetid >=10000|| username.size() >=10 || msg.size() >= 1004)
       return ;
   Userid = UserMsg->getUserId();
   if (UserMsg->getUserName() != "")
   username = UserMsg->getUserName();
   sendMsg.SetCmmd(cmmd);
   sendMsg.SetUserId(Userid);
   sendMsg.SetTargetId(Targetid);
   sendMsg.SetName(username);
   sendMsg.SetBody(msg);

  sendMsg.ShowTheMsg();
    NetWorkConnet->SendIndividualMsg(string(sendMsg.data(),1024));
//    boost::bind(&WeChatConnet::SendIndividualMsg,NetWorkConnet,msg);
}

void WeChatControl::PushBackFuntions(){
    //防止boost的线程不一致
    ReadControlFuntions.push_back(boost::bind(&WeChatControl::ReadResightUser ,this,_1,_2,_3,_4,_5));
    ReadControlFuntions.push_back(boost::bind(&WeChatControl::ReadCheckUser ,this,_1,_2,_3,_4,_5));
    ReadControlFuntions.push_back(boost::bind(&WeChatControl::ReadIndivideMsg ,this,_1,_2,_3,_4,_5));
}

bool WeChatControl::IsConnet(){

    if (dlg->GetIsLogin())
    {
        toshow->LoginShow();
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
void WeChatControl::ReadMsgFromNet(int cmmd, int Userid, int Targetid, string username, string msg){
    cout<<"WeChatControl::ReadMsgFromNet" << cmmd<<endl;

    ReadControlFuntions[cmmd](cmmd,Userid, Targetid, username,msg ) ;
}




void WeChatControl::ReadCheckUser(int cmmd, int Userid, int Targetid, string username, string msg){
    if (cmmd != 1)
        return ;
    UserMsg->setUserId(Userid);
    UserMsg->setUserName(username);
   emit CheckResultFromService(Userid);
}

void WeChatControl::ReadResightUser(int cmmd, int Userid, int Targetid, string username, string msg){

    if (cmmd != 0)
        return ;

    if (Targetid)
       { dlg->AllowResign(true);

        }
    else
        dlg->AllowResign(false);
}


void WeChatControl::ReadFriendsMsg(int cmmd, int Userid, int Max, string username, char* msg){
    if (cmmd != 80)
        return ;
    friendsBuffer friendMsg;
    friendMsg.SetFriendsBuffer(msg);
    int cnt = friendMsg.GetAmouts();
    int number =cnt *2;

    for (int i= 0;i<number;i++)
    {
        string buffer = friendMsg.GetOneFriendMsg(i) ;
        FriendsMsg.push_back(buffer);
    }
    FriendNumbers += cnt ;
    if(FriendNumbers >= Max)
        toshow->LoadFriendMsg(FriendsMsg);
}


void WeChatControl::ReadIndivideMsg(int cmmd, int Userid, int Targetid, string username, string msg){
    if (cmmd != 2)
        return ;
    toshow->ChatMegFromNetWork(Userid,msg,username);
}


string WeChatControl::GetUserName(){
    return UserMsg->getUserName();
}
