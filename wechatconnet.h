#ifndef WECHATCONNET_H
#define WECHATCONNET_H
#include <iostream>
#include <boost/asio.hpp>
#include <string>
#include <map>
#include <boost/smart_ptr.hpp>
using namespace std;
using namespace boost::asio;
class WeChatControl;
class WeChatConnet
{

public:
    WeChatConnet(WeChatControl* Control);
    bool IsConnet(ip::tcp::socket chatsocket, string address);
    bool SendIndividualMsg( const string& Msg);
    bool ReadIndividualMsg(char MessageBuffers[],const boost::system::error_code &e, size_t bytes);
    bool SendGroundMsg();
    bool ReadGroundMsg();
    void ReadHandle();
    void SendHandle(char* buffer);

private :
    WeChatControl* Control;
    io_service We_io_service;
    ip::tcp::endpoint We_endpoint;
    ip::tcp::socket We_socket;
    map<int, boost::shared_ptr<ip::tcp::socket> > socket_map;
    boost::shared_ptr<ip::tcp::socket> We_Socket_ptr;  //暂时用单个socket，等完成差不多，由map或者hasmap来代替
    boost::system::error_code ec;
};

#endif // WECHATCONNET_H
