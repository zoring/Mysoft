#ifndef WECHATSERVICE_H
#define WECHATSERVICE_H
#include <iostream>
#include <map>
#include <string>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <boost/smart_ptr.hpp>
#include <string>
#include "dbcontrol.h"
#include "logincontrol.h"
#include <boost/function.hpp>
#include "elumdata.h"
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
    void SendIndividualMessage(boost::shared_ptr<tcp::socket> ReadSocket,int cmmd,int Userid,int Targetid,string username,string msg);

    //组信息读取和转发
    void ReanGroundMessage(Tcp_Socket_ptr ReadSocket, error_code ec);
    void SendGroundMessage();
    void HandleRead(boost::shared_ptr<tcp::socket> psocket, char MessageBuffer[],const boost::system::error_code& e, size_t bytes);

   // 异步写操作完成后write_handler触发
     void write_handler(boost::shared_ptr<std::string> pstr, error_code ec, size_t bytes_transferred);
     void SendHandle(const boost::system::error_code &e);
     //
     void write_user_message();

     void StartMsgService();
     void StartFuntionService();




private:
        void LoadGroundMsg(int cmmd,int UserId = 0, int TargetId = 0,string userName="",string Msg = "", boost::shared_ptr<tcp::socket> psocket =0);
        void LoadFriendsMsg(int cmmd,int UserId = 0, int TargetId = 0,string userName="",string Msg = "", boost::shared_ptr<tcp::socket> psocket =0,int groundid=0);
        void SightUp(int cmmd,int UserId = 0, int TargetId = 0,string userName="",string Msg = "", boost::shared_ptr<tcp::socket> psocket =0);
         void CheackLogin(int cmmd,int UserId = 0, int TargetId= 0,string userName="",string Msg = "", boost::shared_ptr<tcp::socket> psocket= 0) ;
         void SerchMsg(int cmmd,int UserId = 0, int TargetId = 0,string userName="",string Msg = "", boost::shared_ptr<tcp::socket> psocket =0);
         void SendIndiviMsg(int cmmd,int UserId = 0, int TargetId = 0,string userName="",string Msg = "", boost::shared_ptr<tcp::socket> psocket =0);
         void SendGroundMsg(int cmmd,int UserId = 0, int TargetId = 0,string userName="",string Msg = "", boost::shared_ptr<tcp::socket> psocket =0) ;
         void UpdateMsg(int cmmd,int UserId = 0, int TargetId = 0,string userName="",string Msg = "", boost::shared_ptr<tcp::socket> psocket =0);
         void DeletcMsg(int cmmd,int UserId = 0, int TargetId = 0,string userName="",string Msg = "", boost::shared_ptr<tcp::socket> psocket =0);
         void AddFriends(int cmmd,int UserId = 0, int TargetId = 0,string userName="",string Msg = "", boost::shared_ptr<tcp::socket> psocket =0);
         void AddGround(int cmmd,int UserId = 0, int TargetId = 0,string userName="",string Msg = "", boost::shared_ptr<tcp::socket> psocket =0);
         void AllowAddFriends(int cmmd,int UserId = 0, int TargetId = 0,string userName="",string Msg = "", boost::shared_ptr<tcp::socket> psocket =0);
         void AllowAddGround(int cmmd,int UserId = 0, int TargetId = 0,string userName="",string Msg = "", boost::shared_ptr<tcp::socket> psocket =0);

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
     map<int, Tcp_Socket_ptr> AlwaysUserMap;
     ip::tcp::acceptor tcp_acceptor;
     DBControl* dbControl;
     LoginControl* loginControl;
     int  AllCmd;
     vector< boost::function<void (int ,int , int , string, string, boost::shared_ptr<tcp::socket>)> > WeChatfuntions;
     ElumData elumdata;

};

#endif // WECHATSERVICE_H
