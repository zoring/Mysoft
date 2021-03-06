#include "persongrounditem.h"
#include <string>
#include <QString>
#include "person.h"
#include <list>
#include "QLabel"
#include "QWidget"
#include "QPainter"
#include <iostream>
#include "QEvent"
#include "QMouseEvent"
#include "QDebug"
#include "QHBoxLayout"
#include "netmsgtoshow.h"
#include "chatdialog.h"

using namespace std;
PersonGroundItem::PersonGroundItem(NetMsgToShow *NetToShow,int UserId, const char* UesrName, char* SignWord, map<int, ChatDialog*>  &FriendChatMap,char* ImageUrl,
                                  QWidget *parent):QWidget(parent), NetToShow(NetToShow),FriendChatMap(FriendChatMap),UserId(UserId)
{



    this->UserName = new QLabel(this);
    this->SiginWord = new QLabel(this);
  QString QUesrName(UesrName);
  QString   QSignWord(SignWord);
    UserName->setText(QUesrName);
    SiginWord->setText(QSignWord);
    if(ImageUrl == NULL || ImageUrl == "")
    {
        ImageUrl = "./1.png";
    }
   ImageUrl = "/home/zoring/WeChat/Mysoft/image/1.png";
    this->ImageUrl = ImageUrl;

    this->PersonImage = new QLabel(this);
  PersonImage->setScaledContents(true);


       PersonImage->setPixmap(QPixmap("/home/zoring/WeChat/Mysoft/image/1.png"));


    PersonImage->setFixedSize(40,40);
    PersonImage->move(7,7);
   UserName->move(54,10);
   SiginWord->move(54,27);

  //PersonImage->installEventFilter(this);


}

void PersonGroundItem::mouseDoubleClickEvent (QMouseEvent *event){
    if(event->button() == Qt::LeftButton) {
        if (FriendChatMap.find(UserId) == FriendChatMap.end())
        {ChatDialog* test =  new ChatDialog(NetToShow,this);

         test->show();
         FriendChatMap[UserId] = test;
          test->activateWindow();
          test->UpdateMessage();
        }
        else
        {
            FriendChatMap[UserId]->show();
            FriendChatMap[UserId]->activateWindow();;

        }
    }
}


bool PersonGroundItem::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == PersonImage)
    {
        if(event->type() == QEvent::Paint)
        {

            PersonImage->setAutoFillBackground(true);
            QPainter painter(PersonImage);
            painter.drawPixmap(PersonImage->rect(), QPixmap("/home/zoring/test/1.png"));
        }
    }
    return QWidget::eventFilter(obj, event);
}

//del person from ground
void PersonGroundItem::DelPerson( Person const person){
    PersonGroundItem::personlist.remove(person);
}

//Add person to ground
void PersonGroundItem::AddPerson( Person const person){
    PersonGroundItem::personlist.push_back(person);
}

int PersonGroundItem::getgroundId() const {
    return this->UserId;
}

bool PersonGroundItem::operator ==(const PersonGroundItem& other){
    if (this->getgroundId() != other.getgroundId())
    {
        return false;
    }
    return true;
}


void PersonGroundItem::PushBackNotReadMsg(string Msg,string UserName){
  UserName = UserName + ":\n";
  Msg = UserName +Msg ;
  if (Msg[Msg.size() - 1] != '\n')
      Msg += "\n";
   this->NotReadMsg.push_back(Msg);
     if (FriendChatMap.find(UserId) != FriendChatMap.end())
         FriendChatMap[UserId]->UpdateMessage();
}


vector<string>& PersonGroundItem::PopNotReadMsg(){
    return NotReadMsg;
}

const int PersonGroundItem::GetUserId(){
    return UserId;
}

