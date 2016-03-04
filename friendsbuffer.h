#ifndef FRIENDSBUFFER_H
#define FRIENDSBUFFER_H
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;

class friendsBuffer
{

public:
    enum { friendsAmount = 2 };
    enum { max_body_length = 1002 };
    enum {one_msg = 14};
    enum { max= 71} ;
    friendsBuffer();
    const char* data() const;
    char* data();

    int GetMsgSize();
    int GetAmouts();
    string GetFriendsBuffer();
    void ResetBuffer();

    void SetFriendsBuffer(string buffer);

    string GetOneFriendMsg(int index);
    void ShowFriendsMsg();
private:
char data_[friendsAmount + max_body_length] ;
size_t body_length_;
 void SetFriendAmout(int Amout);
};

#endif // FRIENDSBUFFER_H
