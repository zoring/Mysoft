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
PersonList::PersonList(NetMsgToShow *NetToshow,QListWidget *parent) : QListWidget(parent),NetToshow(NetToshow)
{

connect(this->NetToshow,&NetMsgToShow::StattionFriends,this,&PersonList::GetMsg );

}

//初始化聊天界面
bool PersonList::StaticMainWindow(){

 QHBoxLayout* Hlayout = new QHBoxLayout();
 QVBoxLayout* layout = new QVBoxLayout();
  QVBoxLayout* StaticLists = new QVBoxLayout();
QPushButton* FriendButton = new QPushButton("Friend");
QPushButton* GroundButton = new QPushButton("Ground");
Hlayout->addWidget(FriendButton);

Hlayout->addWidget(GroundButton);
StaticList(StaticLists);
 layout->addItem(Hlayout);
 layout->addItem(StaticLists);
//this->setLayout(layout);
this->show();

 return true ;
}


//获取组信息
bool PersonList::StaticList( QVBoxLayout* layout){

     for (int i =0; i<=10;i++)
     {
         PersonGroundItem*  test = new PersonGroundItem(NetToshow,i,"fd","erf");
          QListWidgetItem* v= new QListWidgetItem();
         v->setSizeHint(QSize(100,120));

          this->insertItem(i,v);


         this->setItemWidget(v,test);
        v->setHidden(false);

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
