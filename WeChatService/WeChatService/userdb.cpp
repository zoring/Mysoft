#include "userdb.h"
#include "databasemsg.h"
UserDB::UserDB(MYSQL* coon):BaseDB(coon)
{

}

vector<string> UserDB::GetAllNotReadMsg(int userId){

}


bool UserDB::SaveMsgRightNow(int cmmd, int ReciveUserId, int SendId, string Msg){
    return true;
}
