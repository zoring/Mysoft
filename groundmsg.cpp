#include "groundmsg.h"

#include <QLineEdit>
GroundMsg::GroundMsg(const string GroundName,const int GroundId,QListWidget  *parent) : QListWidget(parent),GroundName(GroundName),GroundId(GroundId),Count(0),
                                                                                        Open(false)
{
    this->setHidden(true);

}

void GroundMsg::AddGroundMember(const int GroundMemberId,PersonGroundItem* GroundMembers){
  if (GroundMember.find(GroundMemberId) == GroundMember.end())
     { GroundMember[GroundMemberId]= GroundMembers;
       Count++;
       InsertGroundMember(GroundMembers);
     }
}

bool GroundMsg::DeleteGroundMember(const int GroundMemberId){
   if(GroundMember.find(GroundMemberId) != GroundMember.end())
   {   delete GroundMember[GroundMemberId];
       GroundMember.erase(GroundMemberId);
        return true;}
   return false;
}


void GroundMsg::OpendOrCloseGround(){
   //open
   if(Open)
   {   Open = false;
       this->setHidden(false);

   }
   else
   {this->setHidden(true);
       Open= true;
   }
}


void GroundMsg::InsertGroundMember(PersonGroundItem *GroundMembers){
    QListWidgetItem* Member= new QListWidgetItem();
   Member->setSizeHint(QSize(100,120));
    this->insertItem(Count,Member);
   this->setItemWidget(Member,GroundMembers);


}

void GroundMsg::ReviceMegFromNet(int userId, string Meg, string UserName){
    if(GroundMember.find(userId) != GroundMember.end())
     GroundMember[userId]->PushBackNotReadMsg(Meg, UserName);
}

bool GroundMsg::IsOpen(){
    return Open;
}



