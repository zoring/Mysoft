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

int UserDB::CanAddGround(string GroundName, int userid){
    //if has retrun id, if not return 0;
    string Msg = " select * from grounds where GroundsName = '" + GroundName + "' and userid = ' " + IntToString(userid) +" ' ";

    int groundid = 0;
    if (mysql_query(Coon.get(), Msg.data()))
        {
            //wrong sql
            return 1;
        }
    MYSQL_RES *res;
    MYSQL_ROW row;
     res = mysql_use_result(Coon.get());
     if ((row = mysql_fetch_row(res)) != NULL)
     {    groundid= atoi(row[0]);
         mysql_free_result(res);
         return groundid;
     }

     mysql_free_result(res);
        return 0;
}

int UserDB::AddGround(int UserId, string GroundName){

    if (CanAddGround(GroundName,UserId))
        return false ;
    string Msg = "insert grounds values (null,"+ IntToString(UserId) +" , '"+ GroundName + "'); ";

    if (mysql_query(Coon.get(), Msg.data()))
        return false;
   int groundid = CanAddGround(GroundName,UserId);
    return groundid ;
}


bool UserDB::DeleteGround(int UserId, string GroundName){
    if (!CanAddGround(GroundName,UserId))
        return false ;
    string Msg ="delete  from grounds, friends where grounds.groundsname = '"+GroundName +" ' and friends.userid = " + IntToString(UserId);
    if (mysql_query(Coon.get(), Msg.data()))
        return false;
    return true ;
}


bool UserDB::AddFriends(int UserId, int GroundId, int FriendId){

    string Msg = "insert friends values (null, "+ IntToString(UserId) +" , "+ IntToString(FriendId) + " ," + IntToString(GroundId) +" );";
    if (mysql_query(Coon.get(), Msg.data()))
        return false;
    return true ;

}


bool UserDB::DeleteFriends(int UserId, int FriendId){
    string Msg = "delete from friends where userid = " + IntToString(UserId) + " and friendid = " + IntToString(FriendId);
    if (mysql_query(Coon.get(), Msg.data()))
        return false;
    return true ;
}



vector<string> UserDB::IsTahtPerson(int userId, string word_key){
    string Msg = "select userid, username from user where userid != " + IntToString(userId) +" and username like '%" + word_key + "%'";
    return ReturnGroundBySqlstring(Msg);
}
