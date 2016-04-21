#ifndef USERDB_H
#define USERDB_H
#include "databasemsg.h"
#include <vector>
#include <boost/shared_ptr.hpp>
#include "basedb.h"
#include <map>
class UserDB : public BaseDB
{
public:
    UserDB(MYSQL* coon);
    bool SaveMsgRightNow(int cmmd,int ReciveUserId,int SendId,string Msg);
    void SaveMegLater(int cmmd,int ReviceId, int SendId,string Msg);
    string GeMsg(int &SendId,int ReciveId);
    vector<string> GetAllNotReadMsg(int userId);
    vector<string> IsTahtPerson(int userId, string word_key);
    bool NoReadMsg(int UserId);
     map<int, vector<boost::shared_ptr<DataBaseMsg> > >* GetSaVeMesg();
     int AddGround(int UserId,string GroundName);
     bool DeleteGround(int UserId,string GroundName);
     bool AddFriends(int UserId,int GroundId, int FriendId);
     bool DeleteFriends(int UserId, int FriendId);
private:
    map<int, vector<boost::shared_ptr<DataBaseMsg> > > AllSaveMessage;
    void DeleteMsg(int UserId,int SendId);
    int CanAddGround(string GroundName,int userid);

};

#endif // USERDB_H
