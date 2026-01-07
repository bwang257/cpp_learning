/* 
Introduction to Errors and Assertions
- types of errors
- static_assert
- runtime assert()
*/

// types of errors: compile-time errors, run-time errors (checking has performance cost), run time exceptions

#include <iostream>
#define NDEBUG // disables assert() as it has performance impact
#include <cassert> // runtime assertions



namespace SomeLibrary {
  constexpr int Version{2};
}

// recall that concepts can be used for compile-time checking too
auto Square(std::floating_point auto x){
  return x*x;
}

// runtime assertions using assert()
class Character{
  public: 
    Character(std::string name) : name{name}{ };
    std::string GetName(){
      return name;
    }
    std::string name;
};

void LogName(Character* Player){
  if ("Hello"){
    std::cout << "LogName called at Runtime" << std::endl;
  }
  // assert doesn't allow extra arguments so we can 
  // use the fact that string evaluate to true
  assert("Nullptr cannot be passed into LogName" && Player);
  std::cout << Player->GetName() << '\n';
}

int main(){
  // Compile Time Assertions using static_assert
  // c++14 and earlier require message argument 
  static_assert(SomeLibrary::Version >= 2, "Version 2 or later of SomeLibrary is required.");
  static_assert(sizeof(int) >= 4);
  Character Brian{"Brian"};
  Character* ptr = &Brian;
  LogName(ptr);
  assert(false && "please #define NDEBUG"); 
  std::cout << "Assert(false) passes\n";
  Square(4.0);

  // Third Parties have open-srouce assert libraries
  // Boost.Assert --> BOOST_ASSERT_MSG(y != 0, "Cannot divide by zero");
  // Check macros --> CHECK(y != 0) << "Cannot divide by zero";

  return 0;
}