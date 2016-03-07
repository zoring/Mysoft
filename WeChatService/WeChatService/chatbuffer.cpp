#include "chatbuffer.h"
#include <math.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
using namespace std;
ChatBuffer::ChatBuffer():body_length_(0),name_length_(0)
{
    Msg_length_ = Cmmd_length +useriD_length + TargetId_length + Name + max_body_length ;
 memset(data_,0,sizeof(data_)/sizeof(char));
}
void ChatBuffer::SetChatBuffer(char* buffer,int size)
{
    memcpy(data_,buffer,size);
}

void ChatBuffer::SetCmmd(int cmmd){
     if (!CheckNumber(cmmd,Cmmd_length))
         return ;
     std::stringstream ss;
     ss << cmmd;
     std::string str = ss.str();
     memcpy(data_, str.c_str(), Cmmd_length);
}


void ChatBuffer::SetUserId(int userid){
    if (!CheckNumber(userid,useriD_length))
        return ;
    std::stringstream ss;
    ss << userid;
    std::string str = ss.str();
    memcpy(data_ + Cmmd_length, str.c_str(), useriD_length);
}

void ChatBuffer::SetTargetId(int targetid){
    if (!CheckNumber(targetid,TargetId_length))
        return ;
    std::stringstream ss;
    ss << targetid;
    std::string str = ss.str();
    int move = Cmmd_length +useriD_length;
    memcpy(data_+ move,str.c_str(), TargetId_length) ;
}

void ChatBuffer::SetName(string name){
    if (name.size() > Name)
        return ;
    int move = Cmmd_length +useriD_length + TargetId_length ;
    name_length_ = name.size() ;
    memcpy(data_+move, name.c_str(),name_length_) ;
}


void ChatBuffer::SetBody(string msg){
    if (msg.size() > max_body_length)
        return ;
    int move = Cmmd_length +useriD_length + TargetId_length + Name ;
    body_length_  =  msg.size() ;
    memcpy(data_ + move , msg.c_str(), body_length_) ;
}

void ChatBuffer::SetBodyByChar(char *msg)
{
    int move = Cmmd_length +useriD_length + TargetId_length + Name ;

    memcpy(data_ + move , msg, max_body_length) ;
}

bool ChatBuffer::CheckNumber(int Anumbers, int sizes){
    if( Anumbers < 0)
        return false;
    int IsOk = pow((double) 10,sizes) ;
    if ((Anumbers / IsOk) >= 10)
        return false;
    else
        return true;
}


int ChatBuffer::GetCmmd(){
    char Cmmd[Cmmd_length +1] = "";
    strncat(Cmmd, data_, Cmmd_length);
    int cmmd = atoi(Cmmd) ;
    return cmmd;
}


int ChatBuffer::GetUserId(){
    char Userid[useriD_length + 1] ="";
    strncat(Userid,data_ +Cmmd_length, useriD_length);
    int userid = atoi(Userid);
    return userid;
}

int ChatBuffer::GetTargetId(){
    char TargetId[TargetId_length + 1] = "" ;
   int  move = Cmmd_length + useriD_length ;
    strncat(TargetId, data_ +move,TargetId_length);
    int targetid = atoi(TargetId);
    return targetid ;
}

string ChatBuffer::GetName(){
    char name[Name + 1] = "";
    int move =Cmmd_length + useriD_length + TargetId_length;
    strncat(name,data_+move,Name);
    return string(name);
}

string ChatBuffer::GetBody(){
    char body[max_body_length +1] = "";
    int move = Cmmd_length + useriD_length + TargetId_length +Name;
    strncat(body,data_+ move, max_body_length);

    return string(body);
}

char* ChatBuffer::data(){
    return data_;
}

const char* ChatBuffer::data() const{
    return data_;
}

int ChatBuffer::GetMsgSize(){
    return Msg_length_;
}

void ChatBuffer::ShowTheMsg(){
    for (int i=0;i<1024;i++)
    {cout<<data_[i]<<" ";

    }
    cout<<endl;
}


