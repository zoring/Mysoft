#include "wechatservice.h"
#include "generfuntions.h"
#include <boost/thread.hpp>
WeChatService::WeChatService(io_service &msg_iosev, io_service &fun_iosev):message_iosev(msg_iosev), Funtion_iosev(fun_iosev),
                             ReadInMegPoint(tcp::v4(), 1200), ReadGroundMegPoint(ip::udp::v4(), 1200), FuntionPoint(ip::udp::v4(), 1201),
                             tcp_acceptor(msg_iosev,ReadInMegPoint),
                             AllCmd(10)
{
 dbControl = new DBControl();
 loginControl = new LoginControl();


           WeChatfuntions.push_back( boost::bind(&WeChatService::CheackLogin ,this,_1,_2,_3,_4));
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


void WeChatService::CheackLogin(int UserId, int TargetId, string Msg, boost::shared_ptr<tcp::socket> psocket){

    if(loginControl->IsLogin(UserId,Msg))
        AlwaysUserMap[UserId] = psocket;
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
    if(ec) return;
    char*  messageBuffers= new char[1024];
    ReadSocket->async_read_some(buffer(messageBuffers,1024),boost::bind(&WeChatService::HandleRead,this,ReadSocket,messageBuffers,_1,_2));

}


void WeChatService::HandleRead(boost::shared_ptr<tcp::socket> psocket,char MessageBuffers[],const boost::system::error_code &e, size_t bytes){

    if (bytes == 0)
        return;
    //读数据处理
   boost::shared_array<char> msg(MessageBuffers);
   string Msg = string(MessageBuffers);
   int cmmd = atoi(Msg.substr(0,1).c_str()) ;
   int userId = atoi(Msg.substr(2,5).c_str()) ;
   int ToOtherId =  atoi(Msg.substr(6,11).c_str());
   if (Msg.length() > 13)
    Msg = Msg.substr(12,Msg.length());
   else
       Msg = "";

   if (cmmd >= AllCmd or cmmd < 0)
       return ;
  // WeChatfuntions[cmmd](userId,ToOtherId,Msg,psocket) ;
   char*  messageBuffersd= new char[1024];
   psocket->async_read_some(buffer(messageBuffersd,1024),boost::bind(&WeChatService::HandleRead,this,psocket,messageBuffersd,_1,_2));

}







void WeChatService::SendIndividualMessage(boost::shared_ptr<tcp::socket> ReadSocket,string msg=""){
     ReadSocket->async_write_some(buffer(msg,msg.size()),boost::bind(&WeChatService::SendHandle,this,_1));
    
}

void WeChatService::SendHandle(const boost::system::error_code &ec){
    if (ec)
    {
        std::cout << boost::system::system_error(ec).what() << std::endl;
    }
    cout<<"finsh"<<endl;
}
