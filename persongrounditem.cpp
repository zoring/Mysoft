#include "persongrounditem.h"
#include <string>
#include <QString>
#include "person.h"
#include <list>
using namespace std;
PersonGroundItem::PersonGroundItem(const QString Groundname, QListWidget* itemlist):QListWidgetItem(Groundname,itemlist)
{

   PersonGroundItem::setGroundName( Groundname.toStdString());
   PersonGroundItem::setIsHidden(true);
}

//del person from ground
void PersonGroundItem::DelPerson( Person const person){
    PersonGroundItem::personlist.remove(person);
}

//Add person to ground
void PersonGroundItem::AddPerson( Person const person){
    PersonGroundItem::personlist.push_back(person);
}

int PersonGroundItem::getgroundId(){
    return PersonGroundItem::GroundId;
}

bool PersonGroundItem::operator ==(PersonGroundItem other){
    if (this->GroundId != other.GroundId)
    {
        return false;
    }
    return true;
}

