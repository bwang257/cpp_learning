/*
Multiple inheritance using virtual 
*/

#include <iostream>
#include <string>

class a {
  public:
    int my_field{3};
};


class b {
  public:
    int my_field{4};
};


// define class c that inherits from both a,b
class c : public a, public b {
};

// issues arise when a class inherits from two different classes
// that inherit from the same class (diamond problem)
// can define virtual inheritence. Everything works normally
// but when we add more descendants, virtual classes become direct parent classes
class e { 
  public:
    e() = default;
    e(int my_field) : my_field{my_field}{}
    int my_field{5};
};

class f: virtual public e {
  public:
    f() : e(6){}
};

class g: virtual public e {
  public:
    g() : e(7){}
};

// class h directly inherits from e
class h: public f, public g {
};


// multiple inheritance, even with base classes, can still be quite messy and
// is never necessary - there are alternative solutions

// Google Style Guide:
//  Multiple inheritance is permitted, but multiple implementation inheritance is strongly discouraged.

int main(){
  c my_class;

  // naming conflicts are an issue but we can work with it using scope resolution operator and static cast
  std::cout << my_class.a::my_field << "\n";
  std::cout << static_cast<b&>(my_class).my_field << "\n";

  // virtual inheritence
  h my_second_class;
  std::cout << my_second_class.my_field << "\n";
}
