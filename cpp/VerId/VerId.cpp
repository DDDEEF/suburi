#include "VerId.h"

int VerId::counter = 0;

VerId::VerId(){
  id_no = ++counter;
}

int VerId::id()const{
  return id_no;
}
