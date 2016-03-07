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
    bool NoReadMsg(int UserId);
     map<int, vector<boost::shared_ptr<DataBaseMsg> > >* GetSaVeMesg();
private:
    map<int, vector<boost::shared_ptr<DataBaseMsg> > > AllSaveMessage;
    void DeleteMsg(int UserId,int SendId);
};

#endif // USERDB_H
