﻿#include "personlist.h"

#include <iostream>
#include "QLabel"
#include "QWidget"
#include "QLayout"
#include "QGridLayout"
#include "QGroupBox"
#include "QListWidget"
#include "QVBoxLayout"
#include "QHBoxLayout"
#include "persongrounditem.h"
#include "netmsgtoshow.h"
#include "chatdialog.h"
#include <QLineEdit>
#include <QPalette>
#include <QMouseEvent>
PersonList::PersonList(NetMsgToShow *NetToshow,QWidget *parent) : QWidget(parent),NetToshow(NetToshow)
{

connect(this->NetToshow,&NetMsgToShow::StattionFriends,this,&PersonList::GetMsg );
connect(this->NetToshow,&NetMsgToShow::FriendsMsgFormService,this,&PersonList::GetFriendsMsg);
connect(this->NetToshow,&NetMsgToShow::ChatMsgFromNet,this,&PersonList::ReviceMegFromNet);
connect(this->NetToshow,&NetMsgToShow::GroundsMsgFormService,this,&PersonList::GetGroundMsg);
connect(this->NetToshow,&NetMsgToShow::GroundRename,this,&PersonList::AddGroundFromNet);
this->setAutoFillBackground(true);

    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap("/home/zoring/WeChat/Mysoft/image/1.jpg")));
 this->setPalette(palette);

}

//初始化聊天界面
bool PersonList::StaticMainWindow(){
    groupMenu = new QMenu();
       blankMenu = new QMenu();
       personMenu = new QMenu();
       QAction *addGroup = new QAction("添加分组", this);
           QAction *delGroup = new QAction("删除该组", this);
           QAction *rename = new QAction("重命名", this);
           QAction *addBuddy = new QAction("添加好友",this);
               QAction *delBuddy = new QAction("删除好友", this);
               blankMenu->addAction(addGroup);
                   groupMenu->addAction(delGroup);
                   groupMenu->addAction(rename);
                   groupMenu->addAction(addBuddy);
                   personMenu->addAction(delBuddy);


  Hlayout = new QHBoxLayout();
  layoutBox = new QVBoxLayout();
 FriendButton = new QPushButton("Friend");
 GroundButton = new QPushButton("Ground");
Hlayout->addWidget(FriendButton);
Hlayout->addWidget(GroundButton);
StaticLists = new QVBoxLayout();
//StaticList(StaticLists);
 layoutBox->addLayout(Hlayout);
  layoutBox->addLayout(StaticLists);
 this->setLayout(layoutBox);
 this->show();
 connect(addGroup,&QAction::triggered,this,&PersonList::AddGround);
 return true ;
}



//获取组信息
bool PersonList::StaticList(int GroundId, vector<string> friendsMsg){
   int i=0;
   string userid ="";
   if (GroundMsgMap.find(GroundId) == GroundMsgMap.end())
       return false;
   for (vector<string>::iterator iter = friendsMsg.begin(); iter !=friendsMsg.end();++iter,++i)
     {

         if(!(i%2))
         { userid = (*iter);
         }
         else
         {string username = (*iter);
             int usrId = atoi(userid.c_str());
             PersonGroundItem*  GroundMembers = new PersonGroundItem(NetToshow,usrId,username.c_str(),"erf",FriendChatMap);
             FriendDate[usrId] = GroundMembers;
             GroundMsg* Ground =  GroundMsgMap[GroundId] ;
             GroundMemberMapGround[usrId] = Ground;
             Ground->AddGroundMember(usrId,GroundMembers);
         }

     }


     return true;

}


bool PersonList::StaticGround( vector<string> GroundMsgs){
 string Groundid ="";
 int i=0;
    for (vector<string> :: iterator iter=  GroundMsgs.begin(); iter != GroundMsgs.end(); iter++,i++)
    {
        if(!(i%2))
        { Groundid = (*iter);
        }
        else{
            string GroundName = (*iter);
              int GroundId = atoi(Groundid.c_str());
              GroundMsg* Grond = new GroundMsg(GroundName,GroundId);
               QString QGroundName(GroundName.c_str());
             QLabel* ShowGroundName= new QLabel(QGroundName);
              //  ShowGroundName->setStyleSheet("QLabel { background-color : blach; color : blue; }");
              ShowGroundName->setSizeIncrement(QSize(50,80));
             GroundMsgMap[GroundId] =Grond;
             GroundsNameMap[ShowGroundName] = GroundId ;
             StaticLists->addWidget(ShowGroundName);
            StaticLists->addWidget(Grond);
        }
    }

    return true;

}

//添加新的组
void PersonList::AddGroundFromNet(int Groundid,string GroundName){
 if( !Groundid )
     return;
 GroundMsg* Grond = new GroundMsg(GroundName,Groundid);
  QString QGroundName(GroundName.c_str());
QLabel* ShowGroundName= new QLabel(QGroundName);

 ShowGroundName->setSizeIncrement(QSize(50,80));
GroundMsgMap[Groundid] =Grond;
GroundsNameMap[ShowGroundName] = Groundid ;
StaticLists->addWidget(ShowGroundName);
StaticLists->addWidget(Grond);
}

//bool PersonList::DelGround(PersonGroundItem Grounds){
//   Grouds.remove(Grounds);

//}



void PersonList::GetMsg(int number){
    StaticMainWindow();
}


void PersonList::GetFriendsMsg(int GroundId,vector<string> Msg){
    StaticList(GroundId,Msg);
}


void PersonList::ReviceMegFromNet(int userId, string Meg,string UserName){

    FriendDate[userId]->PushBackNotReadMsg(Meg, UserName);
}


void PersonList::GetGroundMsg(vector<string> Msg){
  StaticGround(Msg);
}

void PersonList::contextMenuEvent(QContextMenuEvent *event){
    QWidget::contextMenuEvent(event);
    if(currentItem==NULL)                           //如果点击到的是空白处
        {
            blankMenu->exec(QCursor::pos());
            return;
        }
        if(GroundsNameMap.find(currentItem) != GroundsNameMap.end())    // 如果点击到的是组
            groupMenu->exec(QCursor::pos());
        else                                            //否则点击到的是好友
            personMenu->exec(QCursor::pos());

}


void PersonList::mousePressEvent(QMouseEvent *event){
    QWidget::mousePressEvent(event);
    currentItem =  this->childAt(mapFromGlobal(QCursor::pos()) )  ; //鼠标位置的Item，不管右键左键都获取
     if(event->button()==Qt::LeftButton && currentItem!=NULL && (GroundsNameMap.find(currentItem) != GroundsNameMap.end()))//如果点击的左键并且是点击的是组
     {

          int groundid =  GroundsNameMap[currentItem] ;
          GroundMsgMap[groundid]->OpendOrCloseGround();
          this->update();
     }
}


void PersonList::AddGround(bool isok){

    groupNameEdit = new QLineEdit();
    StaticLists->addWidget(groupNameEdit);
    connect(this->groupNameEdit,&QLineEdit::editingFinished,this,&PersonList::ReGroundname);
}


void PersonList::ReGroundname(){
    QString NewName = groupNameEdit->displayText();
    StaticLists->removeWidget(groupNameEdit);
    disconnect(this->groupNameEdit,&QLineEdit::textChanged,this,&PersonList::ReGroundname);
    delete groupNameEdit;
    groupNameEdit = NULL;
    NetToshow->SendMsgToNet(cmmddata.AddGroundCmmd,0,NewName.toStdString());
}
