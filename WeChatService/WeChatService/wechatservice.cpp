#include "wechatservice.h"
#include <boost/thread.hpp>
WeChatService::WeChatService(io_service &msg_iosev, io_service &fun_iosev):message_iosev(msg_iosev), Funtion_iosev(fun_iosev),
                             ReadInMegPoint(tcp::v4(), 1200), ReadGroundMegPoint(ip::udp::v4(), 1200), FuntionPoint(ip::udp::v4(), 1201),
                             tcp_acceptor(msg_iosev,ReadInMegPoint)
{

}

void WeChatService::StaticConnetion(){
    StartMsgService();
    //boost::thread(StartMsgService);
    //boost::thread(&StartFuntionService);
}

//多线程ｒｕｎ
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

//有信息到来时候
void WeChatService::ReadIndividualMessage(Tcp_Socket_ptr ReadSocket, boost::system::error_code ec){
    ClientTcpConnet();
    if(ec) return;
    char*  messageBuffers= new char[1024];
    cout<<"fdsf"<<endl;
    ReadSocket->async_read_some(buffer(messageBuffers),boost::bind(&WeChatService::HandleRead,this,messageBuffers,_1,_2));

}


void WeChatService::HandleRead(char* MessageBuffers,const boost::system::error_code &e, size_t bytes){
   cout<<bytes<<endl;
    if (bytes == 0)
        return;
   cout<<"MessageBuffer";


}

