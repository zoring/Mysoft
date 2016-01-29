#ifndef WECHATCONNET_H
#define WECHATCONNET_H
#include <iostream>
#include <boost/asio.hpp>
#include <string>
#include <map>
#include <boost/smart_ptr.hpp>
using namespace std;
using namespace boost::asio;

class WeChatConnet
{

public:
    WeChatConnet();
    bool IsConnet(ip::tcp::socket chatsocket, string address);
    bool SendIndividualMsg(boost::shared_ptr<ip::tcp::socket> socket_ptr, const string& Msg);
    bool ReadIndividualMsg(boost::shared_ptr<ip::tcp::socket> socket_ptr);
    bool SendGroundMsg();
    bool ReadGroundMsg();
    void ReadHandle(boost::shared_ptr<ip::tcp::socket> socket_ptr, const boost::system::error_code &err, std::size_t bytes);
    void SendHandle();
private :

    io_service We_io_service;
    ip::tcp::endpoint We_endpoint;
    ip::tcp::socket We_socket;
    map<int, boost::shared_ptr<ip::tcp::socket> > socket_map;
    boost::shared_ptr<ip::tcp::socket> We_Socket_ptr;  //暂时用单个socket，等完成差不多，由map或者hasmap来代替
    boost::system::error_code ec;
};

#endif // WECHATCONNET_H
