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
    enum { max= 41} ;
    friendsBuffer();
    const char* data() const;
    char* data();

    int GetMsgSize();
    int GetAmouts();
    string GetFriendsBuffer();

    void SetFriendAmout(int Amout);
    void SetFriendsBuffer(string buffer);
private:
char data_[friendsAmount + max_body_length] ;
size_t body_length_;

};

#endif // FRIENDSBUFFER_H
