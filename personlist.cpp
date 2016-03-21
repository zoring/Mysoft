#include "personlist.h"

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
#include <QMouseEvent>
PersonList::PersonList(NetMsgToShow *NetToshow,QWidget *parent) : QWidget(parent),NetToshow(NetToshow)
{

connect(this->NetToshow,&NetMsgToShow::StattionFriends,this,&PersonList::GetMsg );
connect(this->NetToshow,&NetMsgToShow::FriendsMsgFormService,this,&PersonList::GetFriendsMsg);
connect(this->NetToshow,&NetMsgToShow::ChatMsgFromNet,this,&PersonList::ReviceMegFromNet);
connect(this->NetToshow,&NetMsgToShow::GroundsMsgFormService,this,&PersonList::GetGroundMsg);

}

//初始化聊天界面
bool PersonList::StaticMainWindow(){
    groupMenu = new QMenu();
       blankMenu = new QMenu();
       QAction *addGroup = new QAction("添加分组", this);
           QAction *delGroup = new QAction("删除该组", this);
           QAction *rename = new QAction("重命名", this);
           blankMenu->addAction(addGroup);
              groupMenu->addAction(delGroup);
              groupMenu->addAction(rename);


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
                ShowGroundName->setStyleSheet("QLabel { background-color : red; color : blue; }");
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
bool PersonList::AddGround(string GroundName){
    QString QGroundName = QString(QString::fromLocal8Bit(GroundName.c_str()));



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


}


void PersonList::GetGroundMsg(vector<string> Msg){
  StaticGround(Msg);
}

void PersonList::contextMenuEvent(QContextMenuEvent *event){
    QWidget::contextMenuEvent(event);


}


void PersonList::mousePressEvent(QMouseEvent *event){
    QWidget::mousePressEvent(event);
   int x= event->globalPos().rx(),y =event->globalPos().ry();
    currentItem =  this->childAt(mapFromGlobal(QCursor::pos()) )  ; //鼠标位置的Item，不管右键左键都获取

     if(event->button()==Qt::LeftButton && currentItem!=NULL && (GroundsNameMap.find(currentItem) != GroundsNameMap.end()))//如果点击的左键并且是点击的是组
     {
         cout<<"OPen"<<endl;
          int groundid =  GroundsNameMap[currentItem] ;
          GroundMsgMap[groundid]->OpendOrCloseGround();
          this->update();
     }
}
