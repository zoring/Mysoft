#include <iostream>
#include "wechatservice.h"
using namespace std;

int main()
{
    io_service iosev1,iosev2;
    WeChatService a(iosev1,iosev2);
    a.StaticConnetion();
    iosev1.run();
    cout << "Hello Wfvborld!" << endl;
    return 0;
}

