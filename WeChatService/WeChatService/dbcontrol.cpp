#include "dbcontrol.h"

DBControl::DBControl()
{
  conn = new ConnetDB();
  conn->Connet();

}


string DBControl::SearService(){

}
