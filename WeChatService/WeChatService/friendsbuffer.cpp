#include "friendsbuffer.h"
#include <iostream>
#include <sstream>
using namespace std;
friendsBuffer::friendsBuffer():body_length_(0)
{

 memset(data_,0,sizeof(data_)/sizeof(char));
}
const char* friendsBuffer::data()const{
    return data_;
}

char* friendsBuffer::data(){
    return data_;
}

int friendsBuffer::GetMsgSize(){
    return body_length_;
}



void friendsBuffer::SetFriendAmout(int Amout){
    if (Amout > max)
        return ;
    std::stringstream ss;
    ss << Amout;
    std::string str = ss.str();
    memcpy(data_, str.c_str(), str.size());
}

void friendsBuffer::SetFriendsBuffer(string buffer){
    if ( buffer.size() > max_body_length)
        return ;
    body_length_ = buffer.size();
     memcpy(data_ + friendsAmount, buffer.c_str(), buffer.size());
}

int friendsBuffer::GetAmouts(){
    char Friends[friendsAmount +1] = "";
    strncat(Friends, data_, friendsAmount);
    int Amouts = atoi(Friends) ;
    return Amouts ;
}

string friendsBuffer::GetFriendsBuffer(){
    char GetFriendsBuffer[max_body_length + 1] = "";
    int move =friendsAmount;
    strncat(GetFriendsBuffer,data_+move,max_body_length);
    return string(GetFriendsBuffer);
}
