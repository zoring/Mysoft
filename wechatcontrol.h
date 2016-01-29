#ifndef WECHATCONTROL_H
#define WECHATCONTROL_H

#include <QObject>
#include "chatdialog.h"
#include "wechatconnet.h"

class WeChatControl
{
public:
    WeChatControl();

private:
    WeChatConnet NetWorkConnet;

};

#endif // WECHATCONTROL_H
