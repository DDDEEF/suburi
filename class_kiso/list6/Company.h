class Employee{
public:
  int number;
  char name[80];
  int salary;
  virtual void showData();
  Employee();
  Employee(int nu, const char* na, int sa);
};

class Director : public Employee{
public:
  int stock;
  void showData();
  Director();
  Director(int nu, const char* na, int sa, int st);
};

class Manager : public Employee{
public:
  int travelAllowance;
  void showData();
  Manager();
  Manager(int nu, const char* na, int sa, int tr);
};

class Salesman : public Employee{
public:
  int sales;
  void showData();
  Salesman();
  Salesman(int nu, const char* na, int sa, int ss);
};
