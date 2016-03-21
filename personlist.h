class NetMsgToShow;

#ifndef PERSONLIST_H
#define PERSONLIST_H
#include "persongrounditem.h"
#include "QListWidget"
#include <QObject>
#include <QVBoxLayout>
#include <iostream>
#include <list>
#include "QPushButton"
#include "groundmsg.h"
#include <vector>
#include <QMenu>
#include <QLabel>
class PersonList : public QWidget
{

public:
    explicit PersonList(NetMsgToShow *NetToshow,QWidget *parent = 0);
    bool StaticMainWindow();
    bool AddGround(std::string GroundName); //增加组

    //bool DelGround(PersonGroundItem Grounds);//删除组
public slots:
    void GetMsg(int number);
    void GetFriendsMsg(int GroundId,vector<string> Msg);
     void ReviceMegFromNet(int TargetId,string Msg,string UserName);
     void GetGroundMsg(vector<string> Msg);
     void contextMenuEvent(QContextMenuEvent *event) ;
     void mousePressEvent(QMouseEvent *event);
private:
    int UserId;
    void ReStaticGoundMsg();
     map<int, ChatDialog*>  FriendChatMap;
    map<int , GroundMsg*>  GroundMsgMap;
    map<int, GroundMsg*> GroundMemberMapGround;
    map<QWidget*,  int> GroundsNameMap;
    std::list<PersonGroundItem> Grouds;   // 组容器
    bool StaticList( int GroundId,vector<string> FriensMsg);
    bool StaticGround(vector<string> GroundMsgs);
    int  OnChageGround();
    NetMsgToShow *NetToshow;
    QVBoxLayout* StaticLists;
    QHBoxLayout* Hlayout ;
    QVBoxLayout* layoutBox;
    QPushButton* FriendButton ;
    QPushButton* GroundButton ;
    QMenu *blankMenu;//点击空白上的菜单
       QMenu *groupMenu;//点击组上的菜单
      QLineEdit *groupNameEdit;//组的名字，重命名的时候需要用到
        QWidget *currentItem;//当前的项
signals:


};

#endif // PERSONLIST_H
