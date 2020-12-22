#include <string>
class Member{
  std::string full_name;
  int no;
  int rank;
public:
  Member(std::string name, int number, int grade);
  int get_rank() { return rank; }
  void set_rank(int grade) { rank = grade; }
  void print();
};
