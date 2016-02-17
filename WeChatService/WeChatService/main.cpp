#include <iostream>

#include "wechatservice.h"

using namespace std;

int main()
{


    io_service iosev1,iosev2;
    WeChatService a(iosev1,iosev2);
    a.StaticConnetion();

    while(1)
    {
    }

    return 0;
}

