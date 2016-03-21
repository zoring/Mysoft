#include "wechatconnet.h"
#include <boost/thread.hpp>
#include "wechatcontrol.h"
#include "chatbuffer.h"
WeChatConnet::WeChatConnet(WeChatControl* control):We_io_service(),We_socket(We_io_service), We_endpoint(ip::address_v4::from_string("127.0.0.1"), 1200)
{
    cout<<"WeChatConnet::WeChat"<<endl;
    We_socket.connect(We_endpoint,ec);
    Control = control ;
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

       Control->PushBackFuntions();
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
    char*  messageBuffersd= new char[1024];

    We_socket.async_read_some(buffer(messageBuffersd,1024),boost::bind(&WeChatConnet::ReadIndividualMsg,this,messageBuffersd,_1,_2));
     if (bytes == 0)
         return false;

         //读数据处理
     cout<<"Has Read Finsh"<<endl;
     ChatBuffer Msg;
     Msg.SetChatBuffer(MessageBuffers,bytes);
     int cmmd = Msg.GetCmmd();
     int userId = Msg.GetUserId();
     int ToOtherId =  Msg.GetTargetId();
     if (cmmd >= 99 or cmmd < 0)
         return false;
    string msg =Msg.GetBody();
    string Name = Msg.GetName();
    delete MessageBuffers;
    if (cmmd!=80 and cmmd!= 81)
    Control->ReadMsgFromNet(cmmd,userId,ToOtherId,Name,msg);
    else
       Control->ReadFriendsMsg(cmmd,userId,ToOtherId,Name,Msg.body());

     return true;
}


void WeChatConnet::SendHandle(char* buffer){
    delete buffer;
    cout<<"Finsh"<<endl;
}
