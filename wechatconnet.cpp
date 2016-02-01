#include "wechatconnet.h"
#include <boost/thread.hpp>

WeChatConnet::WeChatConnet():We_io_service(),We_socket(We_io_service), We_endpoint(ip::address_v4::from_string("127.0.0.1"), 1200)
{
    We_socket.connect(We_endpoint,ec);
    if (ec)
    {
        std::cout << boost::system::system_error(ec).what() << std::endl;

    }

}

bool WeChatConnet::IsConnet(ip::tcp::socket chatsocket, string address){

   ip::tcp::endpoint ep(ip::address_v4::from_string(address), 1201);
   boost::shared_ptr<ip::tcp::socket> Socket_ptr(new ip::tcp::socket(We_io_service));

}


bool WeChatConnet::SendIndividualMsg( const string& Msg = "finsh"){
//    if (!chatsocket->is_open())
//        return false;
   We_socket.async_write_some(buffer(Msg,Msg.size()), boost::bind(&WeChatConnet::SendHandle, this));
        return true;
}



void WeChatConnet::SendHandle(){
    cout<<"Finsh"<<endl;
}
