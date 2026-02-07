/*
User defined Conversions
- overload typecast operators
- explicit keyword
- removing typecasts w/delete

g++ user_defined_conversions.cpp -o run
*/

#include <iostream>
#include <string>
#include <cassert>

// forward declarations
class FictionalCharacter;
class FictionalGroup;


class RealPerson{
  public:
    std::string name;
};


class FictionalGroup{
  public:
    FictionalGroup() : leader{nullptr}{};
    FictionalGroup(const FictionalCharacter* leader) : leader{leader}{};
    const FictionalCharacter* leader;
};

class FictionalCharacter{
  public:
    FictionalCharacter(std::string name) : name{name}{}

    void take_damage(){
      alive = false;
    }

    // typecase operator
    operator bool() const {
      return alive;
    }

    // custom type conversion
    operator FictionalGroup() const {
      return FictionalGroup { this };
    }

    // we can remove typecast overloads
    operator RealPerson() = delete;

    std::string name;
    bool alive{true};
};

void create_fic_group(FictionalGroup group){
  std::cout << "Group created with ";
  if (group.leader){
    std::cout << group.leader->name  << " as leader!\n";
  } else {
    std::cout << "no leader\n";
  }
}


// ex. bools can be converted to floats, ints, etc. 
// compiler allows this but we can make any constructor conversions explicit
struct myIntObj{ 
  explicit myIntObj(int x) : val{x}{}

  // same thing for type casts
  // if bool operator made explicit, C++ allows exceptional behavior for control flow, ! || operators, 
  // and static assert and constexpr statements
  explicit operator int(){
    return val;
  }
  int val;
};

void myfunc(myIntObj x){
  std::cout << x.val << "\n";
}


int main(){
  FictionalCharacter harvey{"Harvey Specter"};
  harvey.take_damage();
  assert(!harvey); // harvey not typecast bool to false
  create_fic_group(harvey); // conversion to FictionalGroup

  myfunc(myIntObj(true)); // no has to be explicit that we are converting somethinbg
  myfunc(static_cast<myIntObj>(5.f));

}