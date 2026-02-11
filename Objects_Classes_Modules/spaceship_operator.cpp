/*
C++20 Spaceship Operator

g++ -std=c++20 spaceship_operator.cpp -o run
*/

// prior to C++20, == and != were different oprators you would have needed to override
// C++20 compiler rewrites the expression A != B to !(A==B) if != operator doesnt exist 
// expression rewriting applied to <=> allows all other combinations

// <=> returns a std::strong_ordering struct with 3 possibilities std::strong_ordering::less/equal/greater
// also equivalent as 4th result, no difference with equal unless talking about levels of equality
// same value vs same memory address objects

// because the == operator is faster than <=>, we explicitly define == and <=>
// why compiler will throw error for == even if <=> defined and 
// we can just have == return A<=>B == std::strong_ordering::equal

#include <iostream>
#include <string>


class Person { 
  public: 
    Person(std::string name, int age) : name{name}, age{age}{}

    bool operator==(const Person& other) const {
      return age == other.age;
    }
    std::strong_ordering operator<=>(const Person& other) const {
      std::cout << "Applying <=> operator!\n";
      return age <=> other.age;
    }
    int age;
    std::string name;
};

int main(){
  Person a{"Brian", 20};
  Person b{"Andrew", 20};
  Person c{"Aman", 19};

  if (a == b){ std::cout << "a == b\n"; }
  if (a > c){ std::cout << "a > c\n"; }
}