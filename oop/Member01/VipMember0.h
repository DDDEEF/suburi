#ifndef ___VipMember0
#define ___VipMember0

#include <string>

class VipMember0{
  std::string full_name;
  int number;
  double weight;
  std::string privilege;
public:
  VipMember0(const std::string& name, int no, double w, const std::string& prv);
  std::string name() const { return full_name; }
  int no() const { return number; }
  double get_weight() const { return weight; }
  void set_weight(double w) { weight = (w > 0) ? w : 0; }
  void print() const;
  std::string get_privilege() const { return privilege; }
  void set_privilege(const std::string& prv){
    privilege = (prv != "") ? prv : "未登録";
  }
};

#endif
