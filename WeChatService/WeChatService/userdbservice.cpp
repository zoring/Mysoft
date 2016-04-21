#include "userdbservice.h"

UserDBService::UserDBService()
{
    conn= new ConnetDB();
  conn->Connet();
  userdb= new UserDB(conn->GetMysqlPtr());
}


int UserDBService::AddGround( int UserId , string GroundName){
    return userdb->AddGround(UserId,GroundName);
}


bool UserDBService::AddFriends(int UserId, int GroundId, int FriendId){
    return userdb->AddFriends(UserId,GroundId,FriendId);
}

bool UserDBService::DeleteFriends(int UserId, int FriendId){
    return userdb->DeleteFriends(UserId,FriendId);
}

bool UserDBService::DeleteGround(int UserId, string GroundName){
    return userdb->DeleteGround(UserId,GroundName);
}

vector<string> UserDBService::GetFoundRusult(int UserId, string key_word){
    return userdb->IsTahtPerson(UserId,key_word);
}
