#include "wechatservice.h"
#include "chatbuffer.h"
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

   if( loginControl->SightUp(UserName,Msg))
       cout<<"Ok, insert data"<<endl;
   else
       cout<<"false "<<endl;
}

void WeChatService::CheackLogin(int cmmd, int UserId, int TargetId, string UserName,string Msg, boost::shared_ptr<tcp::socket> psocket){
    cout<<" WeChatService::CheackLogin" <<endl;

     UserId = loginControl->IsLogin(UserName,Msg) ;
     cout<<UserId<<endl;
    if(UserId)
        AlwaysUserMap[UserId] = psocket;
    SendIndividualMessage(psocket,cmmd,UserId,TargetId,UserName,Msg);

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
    Msg.ShowTheMsg();
   Msg.SetChatBuffer(MessageBuffers,bytes);
   Msg.ShowTheMsg();
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
    cout<<cmmd<<endl;
    ReadSocket->async_write_some(buffer(string(sendMsg.data(),1024)),boost::bind(&WeChatService::SendHandle,this,_1));
    
}

void WeChatService::SendHandle(const boost::system::error_code &ec){
    if (ec)
    {
        std::cout << boost::system::system_error(ec).what() << std::endl;
    }
    cout<<"finsh"<<endl;
}
