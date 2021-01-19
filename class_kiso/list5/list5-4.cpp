#include "MyClass.h"

class NewClass : public MyClass{
public:
  void myFunc();
};

void NewClass::myFunc(){
  pub_data = 123;
  pri_data = 456;
  pro_data = 789; 
}
