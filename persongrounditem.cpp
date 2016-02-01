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
PersonGroundItem::PersonGroundItem(NetMsgToShow *NetToShow,int UserId, char* UesrName, char* SignWord, char* ImageUrl,QWidget *parent):QWidget(parent), NetToShow(NetToShow)
{

    this->UserId = UserId;
    this->UserName = new QLabel(this);
    this->SiginWord = new QLabel(this);
  QString QUesrName(UesrName);
  QString   QSignWord(SignWord);
    UserName->setText("&QUesrName");
    SiginWord->setText("QSignWord");
    if(ImageUrl == NULL || ImageUrl == "")
    {
        ImageUrl = "./1.png";
    }
   ImageUrl = "/home/zoring/WeChat/1.png";

    this->ImageUrl = ImageUrl;
    this->PersonImage = new QWidget(this);
    PersonImage->setFixedSize(40,40);
    PersonImage->move(7,7);
   UserName->move(54,10);
   SiginWord->move(54,27);


  PersonImage->installEventFilter(this);

}

void PersonGroundItem::mouseDoubleClickEvent (QMouseEvent *event){
    if(event->button() == Qt::LeftButton) {

        ChatDialog* test =  new ChatDialog(NetToShow);
         test->show();
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

