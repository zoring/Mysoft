#ifndef USERDBSERVICE_H
#define USERDBSERVICE_H
#include "userdb.h"
#include "connetdb.h"
class UserDBService
{
public:
    UserDBService();
    int AddGround(int UserId , string GroundName);
    bool DeleteGround(int UserId,string GroundName);
    bool AddFriends(int UserId,int GroundId, int FriendId);
    bool DeleteFriends(int UserId, int FriendId);
    vector<string> GetFoundRusult(int UserId,string key_word);
private:
    ConnetDB* conn;
    UserDB* userdb;

};

#endif // USERDBSERVICE_H
