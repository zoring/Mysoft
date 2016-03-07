#ifndef CHATBUFFER_H
#define CHATBUFFER_H
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
using namespace std;
class ChatBuffer
{
public:

    enum { Cmmd_length = 2 };
    enum { useriD_length = 4 };
    enum { TargetId_length = 4 };
    enum { Name = 10 };
    enum { max_body_length = 1004 };
    ChatBuffer();
   void SetChatBuffer(char* buffer,int size);
    const char* data() const;
    char* data();
    int GetMsgSize();
//    size_t length() const;
//    const char* body() const;
//    char* body() ;
//    void body_length(size_t length);

//    const char* uiserId() const;
//    char* uiserId() ;

//    const char* TargetId() const;
//    char* TargetId() ;

//    const char* Name() const;
//    char* Name() ;
//    void Name_length(size_t length);

    void SetCmmd(int cmmd);
    void SetUserId(int userid);
    void SetTargetId(int targetid);
    void SetName(string name);
    void SetBody(string msg);
    void SetBodyByChar(char* msg);
    bool CheckNumber(int Anumbers, int sizes);

    int GetCmmd();
    int GetUserId();
    int GetTargetId();
    string GetName();
    string GetBody();
   void ShowTheMsg();

    private:
    char data_[Cmmd_length +useriD_length + TargetId_length + Name + max_body_length] ;
    size_t body_length_;
    size_t name_length_;
    size_t Msg_length_;

};

#endif // CHATBUFFER_H
