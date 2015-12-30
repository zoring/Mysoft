#include "person.h"

Person::Person()
{
    Person::setisOnline(false); //set online state false
}

//重载==
bool Person::operator ==(Person other){
    if (this->Personid != other.getPersonId()){
        return false;
    }
    return true;
}

//获取personId
int Person::getPersonId(){
    return Personid;
}
