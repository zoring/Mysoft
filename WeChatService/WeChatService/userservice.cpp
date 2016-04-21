#include "userservice.h"
#include "wechatservice.h"
#include "chatbuffer.h"
#include "friendsbuffer.h"
#include "userdbservice.h"

UserService::UserService(WeChatService* wechatservice,map<int, Tcp_Socket_ptr> &AlwaysUserMap ):wechatservice(wechatservice),AlwaysUserMap(AlwaysUserMap),
                                                     userdbservice()
{
loginControl = new LoginControl();
}

void UserService::SightUp(int cmmd,int UserId, int TargetId,string UserName, string Msg, boost::shared_ptr<tcp::socket> psocket){
    if(elumdata.SightInCmmd != cmmd)
        return ;
   if( loginControl->SightUp(UserName,Msg))
       cout<<"Ok, insert data"<<endl;
   else
       cout<<"false "<<endl;
}

void UserService::CheackLogin(int cmmd, int UserId, int TargetId, string UserName,string Msg, boost::shared_ptr<tcp::socket> psocket){
    if (elumdata.LoginCmmd != cmmd)
        return ;
    UserId = loginControl->IsLogin(UserName,Msg) ;
    if(UserId)
       { AlwaysUserMap[UserId] = psocket;
         wechatservice->SendIndividualMessage(psocket,cmmd,UserId,TargetId,UserName,Msg);
         LoadGroundMsg(80,UserId,TargetId,UserName,Msg,psocket);
        }
    else
         wechatservice->SendIndividualMessage(psocket,cmmd,UserId,TargetId,UserName,Msg);


}

void UserService::LoadFriendsMsg(int cmmd, int UserId, int TargetId, string userName, string Msg, boost::shared_ptr<tcp::socket> psocket, int groundid){
    if (! groundid)
        return ;
    vector<boost::shared_ptr<string> > MsgBuffer = loginControl->LoadUserFriends(UserId,groundid);
    friendsBuffer FriendsMsg;
    int max=0;
    max = MsgBuffer.size() /2;
    Msg = "";
    int index = 0;
    for(vector<boost::shared_ptr<string> >::iterator iter= MsgBuffer.begin(); iter != MsgBuffer.end();++iter,++index){

        FriendsMsg.SetOneFriendsBuffer(index,*((*iter).get()));
        if (FriendsMsg.GetMsgSize() >= 71)
        {

          ChatBuffer sendMsg;
          sendMsg.SetCmmd(cmmd);
          sendMsg.SetUserId(groundid);
          sendMsg.SetTargetId(max);
          sendMsg.SetName(userName);
          sendMsg.SetBodyByChar(FriendsMsg.data());
          psocket->async_write_some(buffer(string(sendMsg.data(),1024)),boost::bind(&WeChatService::SendHandle,wechatservice,_1));

          FriendsMsg.ResetBuffer();

        }

    }
    if (FriendsMsg.GetMsgSize())
    {
        ChatBuffer sendMsg;
        sendMsg.SetCmmd(cmmd);
        sendMsg.SetUserId(groundid);
        sendMsg.SetTargetId(max);
        sendMsg.SetName(userName);
        sendMsg.SetBodyByChar(FriendsMsg.data());
        psocket->async_write_some(buffer(string(sendMsg.data(),1024)),boost::bind(&WeChatService::SendHandle,wechatservice,_1));
        FriendsMsg.ResetBuffer();

    }
}


void UserService::LoadGroundMsg(int cmmd, int UserId, int TargetId, string userName, string Msg, boost::shared_ptr<tcp::socket> psocket){
    vector<boost::shared_ptr<string> > MsgBuffer = loginControl->LoadGroundMsg(UserId);
    friendsBuffer FriendsMsg;
    int max=0;
    max = MsgBuffer.size() /2;
    Msg = "";
    int index = 0;
    for(vector<boost::shared_ptr<string> >::iterator iter= MsgBuffer.begin(); iter != MsgBuffer.end();++iter,++index){

        FriendsMsg.SetOneFriendsBuffer(index,*((*iter).get()));
        if (!(index %2))
           {

            int  groundid = atoi((*((*iter).get())).c_str());
            LoadFriendsMsg(81,UserId,TargetId,userName,Msg,psocket,groundid);
        }
        if (FriendsMsg.GetMsgSize() >= 71)
        {

          ChatBuffer sendMsg;
          sendMsg.SetCmmd(cmmd);
          sendMsg.SetUserId(UserId);
          sendMsg.SetTargetId(max);
          sendMsg.SetName(userName);
          sendMsg.SetBodyByChar(FriendsMsg.data());
          psocket->async_write_some(buffer(string(sendMsg.data(),1024)),boost::bind(&WeChatService::SendHandle,wechatservice,_1));

          FriendsMsg.ResetBuffer();

        }

    }
    if (FriendsMsg.GetMsgSize())
    {
        ChatBuffer sendMsg;
        sendMsg.SetCmmd(cmmd);
        sendMsg.SetUserId(UserId);
        sendMsg.SetTargetId(max);
        sendMsg.SetName(userName);
        sendMsg.SetBodyByChar(FriendsMsg.data());
        psocket->async_write_some(buffer(string(sendMsg.data(),1024)),boost::bind(&WeChatService::SendHandle,wechatservice,_1));
        FriendsMsg.ResetBuffer();

    }
}


void UserService::AddGround(int cmmd, int UserId, int TargetId, string UserName, string Msg, boost::shared_ptr<tcp::socket> psocket){
    if(elumdata.AddGroundCmmd != cmmd)
        return ;
   int groundid =  userdbservice.AddGround(UserId,Msg) ;
    if(!groundid)
        return;
    wechatservice->SendIndividualMessage(psocket,cmmd,UserId,groundid,UserName,Msg);
}


void UserService::DeleteGround(int cmmd, int UserId, int TargetId, string UserName, string Msg, boost::shared_ptr<tcp::socket> psocket){
    if(elumdata.DeleteGroundCmmd != cmmd)
        return;
    if(! userdbservice.DeleteGround(UserId,Msg))
        return ;
}

void UserService::AddFriend(int cmmd, int UserId, int TargetId, string UserName, string Msg, boost::shared_ptr<tcp::socket> psocket){
    if (elumdata.AddFriendCmmd != cmmd)
        return ;
    int GroundId = atoi(Msg.c_str());
    if (! userdbservice.AddFriends(UserId,GroundId,TargetId))
        return ;
}

void UserService::DeleteFriends(int cmmd, int UserId, int TargetId, string UserName, string Msg, boost::shared_ptr<tcp::socket> psocket){
    if (elumdata.DeleteFriendCmmd != cmmd)
        return ;
    if(! userdbservice.DeleteFriends(UserId,TargetId))
        return;
}

void UserService::FindFriendsMsg(int cmmd, int UserId, int TargetId, string UserName, string Msg, boost::shared_ptr<tcp::socket> psocket){
    if (elumdata.FindFriendscmmd != cmmd)
        return ;
    FingFriendMsg(51,UserId,TargetId,UserName,Msg ,psocket);
}


void UserService::FingFriendMsg(int cmmd, int UserId, int TargetId, string userName, string Msg, boost::shared_ptr<tcp::socket> psocket){
    vector<string> MsgBuffer = userdbservice.GetFoundRusult(UserId,Msg);
    friendsBuffer FriendsMsg;
    int max=0;
    max = MsgBuffer.size() /2;
    Msg = "";
    int index = 0;
    for(vector<string>::iterator iter= MsgBuffer.begin(); iter != MsgBuffer.end();++iter,++index){

        FriendsMsg.SetOneFriendsBuffer(index,*(iter));

        if (FriendsMsg.GetMsgSize() >= 71)
        {

          ChatBuffer sendMsg;
          sendMsg.SetCmmd(cmmd);
          sendMsg.SetUserId(UserId);
          sendMsg.SetTargetId(max);
          sendMsg.SetName(userName);
          sendMsg.SetBodyByChar(FriendsMsg.data());
          psocket->async_write_some(buffer(string(sendMsg.data(),1024)),boost::bind(&WeChatService::SendHandle,wechatservice,_1));

          FriendsMsg.ResetBuffer();

        }

    }
    if (FriendsMsg.GetMsgSize())
    {
        ChatBuffer sendMsg;
        sendMsg.SetCmmd(cmmd);
        sendMsg.SetUserId(UserId);
        sendMsg.SetTargetId(max);
        sendMsg.SetName(userName);
        sendMsg.SetBodyByChar(FriendsMsg.data());
        psocket->async_write_some(buffer(string(sendMsg.data(),1024)),boost::bind(&WeChatService::SendHandle,wechatservice,_1));
        FriendsMsg.ResetBuffer();

    }
}
