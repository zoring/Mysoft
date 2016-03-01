#include "wechatconnet.h"
#include <boost/thread.hpp>

WeChatConnet::WeChatConnet():We_io_service(),We_socket(We_io_service), We_endpoint(ip::address_v4::from_string("127.0.0.1"), 1200)
{
    We_socket.connect(We_endpoint,ec);

    if (ec)
    {
        std::cout << boost::system::system_error(ec).what() << std::endl;

    }

    boost::thread(boost::bind(&WeChatConnet::ReadHandle,this));
}

bool WeChatConnet::IsConnet(ip::tcp::socket chatsocket, string address){

   ip::tcp::endpoint ep(ip::address_v4::from_string(address), 1201);
   boost::shared_ptr<ip::tcp::socket> Socket_ptr(new ip::tcp::socket(We_io_service));

}
void WeChatConnet::ReadHandle(){


      char*  messageBuffersd= new char[1024];

      We_socket.async_read_some(buffer(messageBuffersd,1024),boost::bind(&WeChatConnet::ReadIndividualMsg,this,messageBuffersd,_1,_2));
      We_io_service.run();
}

bool WeChatConnet::SendIndividualMsg( const string& Msg = "finsh"){
//    if (!chatsocket->is_open())
//        return false;

   char* msg =new char[1024] ;
   std::copy(Msg.begin(),Msg.end(),msg);

   We_socket.async_write_some(buffer(msg,Msg.size()), boost::bind(&WeChatConnet::SendHandle, this,msg));
        return true;
}

bool WeChatConnet::ReadIndividualMsg(char MessageBuffers[], const boost::system::error_code &e, size_t bytes){
    cout<<"Has readed"<<endl;
     if (bytes == 0)
         return false;
     //读数据处理

     for (size_t index=0; index < bytes;++index)
     {cout<<MessageBuffers[index];

     }
    cout<<"this is ok"<<endl;
    boost::shared_array<char> msg(MessageBuffers);

     char*  messageBuffersd= new char[1024];
      We_socket.async_read_some(buffer(messageBuffersd,1024),boost::bind(&WeChatConnet::ReadIndividualMsg,this,messageBuffersd,_1,_2));

     return true;
}


void WeChatConnet::SendHandle(char* buffer){
    delete buffer;
    cout<<"Finsh"<<endl;
}
