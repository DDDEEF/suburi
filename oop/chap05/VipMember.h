#ifndef ___VipMember
#define ___VipMember

#include <string>
#include "Member.h"

class VipMember : public Member{
  std::string privilege;
public:
  VipMember(const std::string& name, int no, double w, const std::string& pv);

  void print() const;

  std::string get_privilege() const { return privilege; }

  void set_privilege(const std::string& prv){
    privilege = (prv != "") ? prv : "未登録";
  }
};

#endif
