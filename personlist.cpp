#include "personlist.h"
#include "QPushButton"
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
PersonList::PersonList(NetMsgToShow *NetToshow,QListWidget *parent) : QListWidget(parent),NetToshow(NetToshow)
{

connect(this->NetToshow,&NetMsgToShow::StattionFriends,this,&PersonList::GetMsg );
connect(this->NetToshow,&NetMsgToShow::FriendsMsgFeomService,this,&PersonList::GetFriendsMsg);
connect(this->NetToshow,&NetMsgToShow::ChatMegFromNetWork,this,&PersonList::ReviceMegFromNet);
}

//初始化聊天界面
bool PersonList::StaticMainWindow(){

 QHBoxLayout* Hlayout = new QHBoxLayout();
 QVBoxLayout* layout = new QVBoxLayout();
   StaticLists = new QVBoxLayout();
QPushButton* FriendButton = new QPushButton("Friend");
QPushButton* GroundButton = new QPushButton("Ground");
Hlayout->addWidget(FriendButton);

Hlayout->addWidget(GroundButton);
//StaticList(StaticLists);
 layout->addItem(Hlayout);
 layout->addItem(StaticLists);
//this->setLayout(layout);
this->show();

 return true ;
}


//获取组信息
bool PersonList::StaticList( vector<string> friendsMsg){
   int i=0;
    string userid ="";
     for (vector<string>::iterator iter = friendsMsg.begin(); iter !=friendsMsg.end();++iter,++i)
     {

         if(!(i%2))
         { userid = (*iter);
         }
         else
         {string username = (*iter);
             int usrId = atoi(userid.c_str());
             PersonGroundItem*  test = new PersonGroundItem(NetToshow,usrId,username.c_str(),"erf",FriendChatMap);
             FriendsData[usrId]  = test;
               QListWidgetItem* v= new QListWidgetItem();
              v->setSizeHint(QSize(100,120));
               this->insertItem(i/2,v);
              this->setItemWidget(v,test);
             v->setHidden(false);
         }



     }




     return true;

}

//获取好友列表信息
bool PersonList::StaticGround(string keys){


    return true;

}

//添加新的组
bool PersonList::AddGround(string GroundName){
    QString QGroundName = QString(QString::fromLocal8Bit(GroundName.c_str()));



}

//bool PersonList::DelGround(PersonGroundItem Grounds){
//   Grouds.remove(Grounds);

//}



void PersonList::GetMsg(int number){
    StaticMainWindow();
}


void PersonList::GetFriendsMsg(vector<string> Msg){
    StaticList(Msg);
}


void PersonList::ReviceMegFromNet(int userId, string Meg){
    FriendsData[userId]->PushBackNotReadMsg(Meg);
}
