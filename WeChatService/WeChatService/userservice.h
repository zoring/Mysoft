class WeChatService;
#ifndef USERSERVICE_H
#define USERSERVICE_H
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include "logincontrol.h"
#include <boost/function.hpp>
#include "elumdata.h"
#include "userdbservice.h"
using namespace boost::asio;
using boost::system::error_code;
using namespace std;
using ip::tcp;
using ip::udp;
class UserService
{ typedef boost::shared_ptr<tcp::socket> Tcp_Socket_ptr;
public:
    UserService( WeChatService* wechatservice,map<int, Tcp_Socket_ptr> &AlwaysUserMap );
    void SightUp(int cmmd,int UserId, int TargetId,string UserName, string Msg, boost::shared_ptr<tcp::socket> psocket);
    void CheackLogin(int cmmd, int UserId, int TargetId, string UserName,string Msg, boost::shared_ptr<tcp::socket> psocket);
    void AddGround(int cmmd, int UserId, int TargetId, string UserName,string Msg, boost::shared_ptr<tcp::socket> psocket);
    void DeleteGround(int cmmd, int UserId, int TargetId, string UserName,string Msg, boost::shared_ptr<tcp::socket> psocket);
    void AddFriend(int cmmd, int UserId, int TargetId, string UserName,string Msg, boost::shared_ptr<tcp::socket> psocket);
    void DeleteFriends(int cmmd, int UserId, int TargetId, string UserName,string Msg, boost::shared_ptr<tcp::socket> psocket);
    void FindFriendsMsg(int cmmd, int UserId, int TargetId, string UserName,string Msg, boost::shared_ptr<tcp::socket> psocket);
private:
    WeChatService* wechatservice;
    map<int, Tcp_Socket_ptr> &AlwaysUserMap;
    ElumData elumdata;
    LoginControl* loginControl;
    UserDBService userdbservice;
    void LoadFriendsMsg(int cmmd, int UserId, int TargetId, string userName, string Msg, boost::shared_ptr<tcp::socket> psocket, int groundid);
    void LoadGroundMsg(int cmmd, int UserId, int TargetId, string userName, string Msg, boost::shared_ptr<tcp::socket> psocket);
    void FingFriendMsg(int cmmd, int UserId, int TargetId, string userName, string Msg, boost::shared_ptr<tcp::socket> psocket);
};

#endif // USERSERVICE_H
