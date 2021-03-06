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

void friendsBuffer::ResetBuffer(){
    body_length_ = 0;
     memset(data_,0,sizeof(data_)/sizeof(char));
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


void friendsBuffer::ShowFriendsMsg(){
    for (int i=0;i<1004;i++)
    {cout<<data_[i]<<" ";

    }
    cout<<endl;
}

void friendsBuffer::SetOneFriendsBuffer(int index, string buffer){
    int move = 0;
    if (!(index %2))
     {move = friendsAmount +(index/2)*14 ;

    }
    else
       {move = friendsAmount + (index/2)*14 + 4;
        body_length_++;
        SetFriendAmout(body_length_);
    }
    memcpy(data_ + move, buffer.c_str(), buffer.size());
}
