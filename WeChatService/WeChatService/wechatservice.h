#ifndef WECHATSERVICE_H
#define WECHATSERVICE_H
#include <iostream>
#include <map>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/smart_ptr.hpp>
using namespace boost::asio;
using boost::system::error_code;
using namespace std;
using ip::tcp;
using ip::udp;
class WeChatService
{
    typedef ip::tcp::socket IndividuaChatSocket;
    typedef ip::udp::socket GroundChatSocket;
    typedef boost::shared_ptr<tcp::socket> Tcp_Socket_ptr;
    typedef boost::shared_ptr<ip::udp::socket> Udp_Service_ptr;
public:
    WeChatService(io_service &msg_iosev, io_service &fun_iosev);
    void StaticConnetion();
    void ClientTcpConnet();
    // 有客户端连接时accept_handler触发
     void accept_handler(Tcp_Socket_ptr psocket, error_code ec);

    //私人聊天信息读取和转发
    void ReadIndividualMessage(boost::shared_ptr<tcp::socket> ReadSocket, boost::system::error_code ec);
    void SendIndividualMessage();
    //组信息读取和转发
    void ReanGroundMessage(Tcp_Socket_ptr ReadSocket, error_code ec);
    void SendGroundMessage();
    void HandleRead(char* MessageBuffer,const boost::system::error_code& e, size_t bytes);

   // 异步写操作完成后write_handler触发
     void write_handler(boost::shared_ptr<std::string> pstr, error_code ec, size_t bytes_transferred);
     //
     void write_user_message();

     void StartMsgService();
     void StartFuntionService();


private:
     //信息的ｓｅｒｖｉｃｅ和　功能的ｓｅｒｖｉｃｅ
     io_service &message_iosev ;
     io_service &Funtion_iosev;

     //端口
     ip::address IpAddress = ip::address::from_string("127.0.0.1");  //ｓｅｒｖｉｃｅ地址
     ip::tcp::endpoint ReadInMegPoint ;  // 私信接收类型和端口
     ip::udp::endpoint ReadGroundMegPoint ;
     ip::udp::endpoint FuntionPoint;

     //
     vector< boost::shared_ptr<boost::thread> > TcpServiceList;
     vector< boost::shared_ptr<tcp::socket> > SocketPtrs;
     //相关辅助记录
     map<string, Tcp_Socket_ptr> AlwaysUserMap;
     ip::tcp::acceptor tcp_acceptor;



};

#endif // WECHATSERVICE_H
