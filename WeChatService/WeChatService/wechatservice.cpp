#include "wechatservice.h"
#include "chatbuffer.h"
#include "friendsbuffer.h"
#include <boost/thread.hpp>
WeChatService::WeChatService(io_service &msg_iosev, io_service &fun_iosev):message_iosev(msg_iosev), Funtion_iosev(fun_iosev),
                             ReadInMegPoint(tcp::v4(), 1200), ReadGroundMegPoint(ip::udp::v4(), 1200), FuntionPoint(ip::udp::v4(), 1201),
                             tcp_acceptor(msg_iosev,ReadInMegPoint),
                             AllCmd(90)
{
 dbControl = new DBControl();
 loginControl = new LoginControl();
        WeChatfuntions.push_back( boost::bind(&WeChatService::SightUp ,this,_1,_2,_3,_4,_5,_6));
        WeChatfuntions.push_back( boost::bind(&WeChatService::CheackLogin ,this,_1,_2,_3,_4,_5,_6));
        WeChatfuntions.push_back( boost::bind(&WeChatService::SendIndiviMsg, this, _1,_2,_3,_4,_5,_6));
//          WeChatfuntions.push_back(boost::bind(&WeChatService::SerchMsg ,this,_1,_2,_3,_4));
//          WeChatfuntions.push_back(boost::bind(&WeChatService::SendIndiviMsg ,this,_1,_2,_3,_4));
//          WeChatfuntions.push_back (boost::bind(&WeChatService::SendGroundMsg ,this,_1,_2,_3,_4) ) ;
//            WeChatfuntions.push_back( boost::bind(&WeChatService::UpdateMsg ,this,_1,_2,_3,_4));
//            WeChatfuntions.push_back( boost::bind(&WeChatService::DeletcMsg ,this,_1,_2,_3,_4));
//           WeChatfuntions.push_back( boost::bind(&WeChatService::AddFriends ,this,_1,_2,_3,_4));
//           WeChatfuntions.push_back( boost::bind(&WeChatService::AddGround ,this,_1,_2,_3,_4));
//          WeChatfuntions.push_back(boost::bind(&WeChatService::AllowAddFriends ,this,_1,_2,_3,_4));
//           WeChatfuntions.push_back( boost::bind(&WeChatService::AllowAddGround ,this,_1,_2,_3,_4));



}


void WeChatService::SightUp(int cmmd,int UserId, int TargetId,string UserName, string Msg, boost::shared_ptr<tcp::socket> psocket){
    if(elumdata.SightInCmmd != cmmd)
        return ;
   if( loginControl->SightUp(UserName,Msg))
       cout<<"Ok, insert data"<<endl;
   else
       cout<<"false "<<endl;
}

void WeChatService::CheackLogin(int cmmd, int UserId, int TargetId, string UserName,string Msg, boost::shared_ptr<tcp::socket> psocket){
    if (elumdata.LoginCmmd != cmmd)
        return ;
    cout<<" WeChatService::CheackLogin" <<endl;
    cout<<UserName<<":"<<Msg<<endl;
    UserId = loginControl->IsLogin(UserName,Msg) ;
    cout<<"UserId:"<<UserId<<endl;
    if(UserId)
       { AlwaysUserMap[UserId] = psocket;
         SendIndividualMessage(psocket,cmmd,UserId,TargetId,UserName,Msg);
         LoadGroundMsg(80,UserId,TargetId,UserName,Msg,psocket);
        }
    else
         SendIndividualMessage(psocket,cmmd,UserId,TargetId,UserName,Msg);


}

 void WeChatService::SendIndiviMsg(int cmmd,int UserId, int TargetId,string userName,string Msg , boost::shared_ptr<tcp::socket> psocket){
     if (elumdata.ChatCmmd != cmmd)
         return;
     cout<<UserId<<"::"<<TargetId<<endl;
     if (AlwaysUserMap.find(TargetId) == AlwaysUserMap.end())
     {
         return ;
     }
     else
     SendIndividualMessage(AlwaysUserMap[TargetId],elumdata.ChatCmmd,UserId,TargetId,userName,Msg);
 }

void WeChatService::LoadFriendsMsg(int cmmd, int UserId, int TargetId, string userName, string Msg, boost::shared_ptr<tcp::socket> psocket, int groundid){
    cout<<"Hello"<<endl;
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
          psocket->async_write_some(buffer(string(sendMsg.data(),1024)),boost::bind(&WeChatService::SendHandle,this,_1));

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
        psocket->async_write_some(buffer(string(sendMsg.data(),1024)),boost::bind(&WeChatService::SendHandle,this,_1));
        FriendsMsg.ResetBuffer();

    }
}


void WeChatService::SerchMsg(int cmmd,int UserId, int TargetId, string UserName,string Msg, boost::shared_ptr<tcp::socket> psocket){

}

void WeChatService::StaticConnetion(){

    boost::thread(boost::bind(&WeChatService::StartMsgService,this));
   // boost::thread(boost::bind(&WeChatService::StartMsgService,this)).join();
}

////多线程ｒｕｎ
void WeChatService::StartMsgService(){

    ClientTcpConnet();
    for (int i=0;i<6;i++)
    {   boost::shared_ptr<boost::thread> pt(new boost::thread(
                                            boost::bind(&boost::asio::io_service::run, &message_iosev))
                                            );
        TcpServiceList.push_back(pt);

    }

}



void WeChatService::ClientTcpConnet(){
    WeChatService::Tcp_Socket_ptr Tcp_Socket(new tcp::socket(message_iosev));
    tcp_acceptor.async_accept(*Tcp_Socket, boost::bind(&WeChatService::ReadIndividualMessage, this,Tcp_Socket, _1));

}

////有信息到来时候
void WeChatService::ReadIndividualMessage(Tcp_Socket_ptr ReadSocket, boost::system::error_code ec){
    cout<<"fdsfsd"<<endl;
    if(ec) return;

    char*  messageBuffers= new char[1024];
    ReadSocket->async_read_some(buffer(messageBuffers,1024),boost::bind(&WeChatService::HandleRead,this,ReadSocket,messageBuffers,_1,_2));
    WeChatService::Tcp_Socket_ptr Tcp_Socket(new tcp::socket(message_iosev));
    tcp_acceptor.async_accept(*Tcp_Socket, boost::bind(&WeChatService::ReadIndividualMessage, this,Tcp_Socket, _1));
}


void WeChatService::HandleRead(boost::shared_ptr<tcp::socket> psocket,char MessageBuffers[],const boost::system::error_code &e, size_t bytes){
   cout<<bytes<<endl;
    if (bytes == 0)
        return;
    //读数据处理
   ChatBuffer Msg;
   Msg.SetChatBuffer(MessageBuffers,bytes);
   int cmmd = Msg.GetCmmd();
   int userId = Msg.GetUserId();
   int ToOtherId =  Msg.GetTargetId();
   if (cmmd >= AllCmd or cmmd < 0)
       return ;
  string msg =Msg.GetBody();
  string Name = Msg.GetName();
  delete MessageBuffers ;
  WeChatfuntions[cmmd](cmmd,userId,ToOtherId,Name,msg,psocket) ;
   char*  messageBuffersd= new char[1024];
   psocket->async_read_some(buffer(messageBuffersd,1024),boost::bind(&WeChatService::HandleRead,this,psocket,messageBuffersd,_1,_2));

}







void WeChatService::SendIndividualMessage(boost::shared_ptr<tcp::socket> ReadSocket,int cmmd,int Userid,int Targetid,string username,string msg){
  cout<<" WeChatService::SendIndividualMessage" <<endl;
    ChatBuffer sendMsg;
    if (cmmd >99 || Userid >=10000 || Targetid >=10000|| username.size() >=10 || msg.size() >= 1004)
        return ;
    sendMsg.SetCmmd(cmmd);
    sendMsg.SetUserId(Userid);
    sendMsg.SetTargetId(Targetid);
    sendMsg.SetName(username);
    sendMsg.SetBody(msg);
    cout<<"Now:"<<msg<<endl;
    ReadSocket->async_write_some(buffer(string(sendMsg.data(),1024)),boost::bind(&WeChatService::SendHandle,this,_1));
    
}




void WeChatService::SendHandle(const boost::system::error_code &ec){
    if (ec)
    {
        std::cout << boost::system::system_error(ec).what() << std::endl;
    }
    cout<<"finsh"<<endl;
}



void WeChatService::LoadGroundMsg(int cmmd, int UserId, int TargetId, string userName, string Msg, boost::shared_ptr<tcp::socket> psocket){
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
          psocket->async_write_some(buffer(string(sendMsg.data(),1024)),boost::bind(&WeChatService::SendHandle,this,_1));

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
        psocket->async_write_some(buffer(string(sendMsg.data(),1024)),boost::bind(&WeChatService::SendHandle,this,_1));
        FriendsMsg.ResetBuffer();

    }
}
