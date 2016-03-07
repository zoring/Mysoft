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

void friendsBuffer::SetFriendsBuffer(char* buffer){


     memcpy(data_  , buffer, max_body_length+ friendsAmount);

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


string friendsBuffer::GetOneFriendMsg(int index){
    int move = 0;
    int length = 0;
    if (!(index %2))
     {move = friendsAmount +(index/2)*14 ;
        length = 4;

    }
    else
       {move = friendsAmount + (index/2)*14 + 4;
        length = 10 ;

    }


    char friendMsg[11] = "";
    strncat(friendMsg,data_+move,length);
    return string(friendMsg);
}

void friendsBuffer::ShowFriendsMsg(){
    for (int i=0;i<1004;i++)
    {cout<<data_[i]<<" ";

    }
    cout<<endl;
}
