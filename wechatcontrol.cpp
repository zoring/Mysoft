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

    NetWorkConnet = new WeChatConnet(this);
    dlg= new LoginDialog(this);
    dlg->show();
    toshow = new NetMsgToShow(this);
    UserMsg = new PersonData();
    PushBackFunByChar();
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
    ReadControlFuntions.push_back(boost::bind(&WeChatControl::ReadAddGround ,this,_1,_2,_3,_4,_5));

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


void WeChatControl::ReadFriendsMsg(int cmmd, int GroundId, int Max, string username, char* msg){

     if(cmmd != 81)
        return;
    friendsBuffer friendMsg;
    friendMsg.SetFriendsBuffer(msg);
    int cnt = friendMsg.GetAmouts();
    int number =cnt *2;
    if (groundMapFriend.find(GroundId) == groundMapFriend.end())
    { vector<string> FriendsMsg;

        groundMapFriend[GroundId] = FriendsMsg;
    }
    for (int i= 0;i<number;i++)
    {
        string buffer = friendMsg.GetOneFriendMsg(i) ;
        groundMapFriend[GroundId].push_back(buffer);
    }

    if(groundMapFriend[GroundId].size() >= Max)
       {if(HasReadGrounds.find(GroundId) != HasReadGrounds.end())
        {

        toshow->LoadFriendMsg(GroundId,groundMapFriend[GroundId]);
        }
        else
            HasReadGrounds.insert(GroundId);
    }
}


void WeChatControl::ReadIndivideMsg(int cmmd, int Userid, int Targetid, string username, string msg){
    if (cmmd != 2)
        return ;
    toshow->ChatMegFromNetWork(Userid,msg,username);
}


string WeChatControl::GetUserName(){
    return UserMsg->getUserName();
}


void WeChatControl::ReadGroundMsg(int cmmd, int Userid, int Max, string username, char *msg){
    if (cmmd != 80 )
    {

        return ;
    }
    friendsBuffer friendMsg;
    friendMsg.SetFriendsBuffer(msg);
    int cnt = friendMsg.GetAmouts();
    int number =cnt *2;

    for (int i= 0;i<number;i++)
    {
        string buffer = friendMsg.GetOneFriendMsg(i) ;
        FriendsGroundMsg.push_back(buffer);
    }
    FriendGroundsNumbers += cnt ;
    if(FriendGroundsNumbers >= Max)
    {
        toshow->LoadGroundsMsg(FriendsGroundMsg);
        for (int i= 0;i<number;i++)
        {
            if(!(i%2))
            {int GroundId = atoi(friendMsg.GetOneFriendMsg(i).c_str());
                if(HasReadGrounds.find(GroundId) != HasReadGrounds.end())
                {
                   if(groundMapFriend.find(GroundId) != groundMapFriend.end())
                    toshow->LoadFriendMsg(GroundId,groundMapFriend[GroundId]);
                   else
                       cout<<"Key False, GroundId  not in groundMapFriend"<<endl;
                }
                else
                    HasReadGrounds.insert(GroundId);
            }
        }
    }
}


void WeChatControl::ReadAddGround(int cmmd, int Userid, int Targetid, string username, string msg){
    if (cmmd != elumdata.AddGroundCmmd)
        return ;
    toshow->GetNewGroundName(Targetid,msg);
}


void WeChatControl::ReadFoundFriendResult(int cmmd, int Userid, int Targetid, string username, char *msg){
    friendsBuffer friendMsg;
    friendMsg.SetFriendsBuffer(msg);
    int cnt = friendMsg.GetAmouts();
    int number =cnt *2;

    for (int i= 0;i<number;i++)
    {
        string buffer = friendMsg.GetOneFriendMsg(i) ;
        FoundFriends.push_back(buffer);
    }
    if (FoundFriends.size() >= Targetid)
    {

    }
}



void WeChatControl::ReadMsgFromNetByChar(int cmmd, int Userid, int Targetid, string username, char *msg){
    if (readFunFromNet.find(cmmd) == readFunFromNet.end())
        return ;
    readFunFromNet[cmmd](cmmd,Userid,Targetid,username,msg);
}



void WeChatControl::PushBackFunByChar(){

    readFunFromNet[81] = boost::bind(&WeChatControl::ReadFriendsMsg ,this,_1,_2,_3,_4,_5);
    readFunFromNet[80] = boost::bind(&WeChatControl::ReadGroundMsg ,this,_1,_2,_3,_4,_5);
}
