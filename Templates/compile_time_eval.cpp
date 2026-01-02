/**
Introduction to compile-time evaluation
- constexpr
- consteval
*/

#include <iostream>
#include <type_traits>
#include <utility>

using std::cout;
using std::endl;


// C++ programs try to do as much at compile time as possible as
// - can improve performance by completing expensive calculations in advance
// - can improve stability of the program, errors preferably occur at compile time
// - unlocks new metapogramming techniques involving more advanced use of templates


// additional notes:
// - **member functions can be made constexpr or consteval along with operators**

template <int someInt>
struct Resource {
  int val{someInt};
};


// can add constexpr to a function so that it is evaluated at compile time
// can also be used at run time too
constexpr int get_int(){
  // can't do anything not possible at compile time (ex. can't print anything)
  return 42;
}

// use std::is_constant_evaluated() to check if a function is evaluated at compile time
// this is a c++ 20 feature: use g++ -std=c++20
constexpr int get_another_int(){
  if (std::is_constant_evaluated()){
    return 21;
  }
  return 42;
}

// use consteval for functions that should only be usable at compile time
// Immediate Functions --> once compilter sees code invoking consteval function, compilter must perform the invocation immediately
// compilation error if ran at runtime
// makes purpose of these functions clearer
consteval int Add(int x, int y){
  return x+y;
}


int main(){
  // templates are defined at compile-time
  // can declare a variable as constexp to let the compiler know its value at compile time
  // these objects are consturcted at compile time
  constexpr int SomeValue{24};
  constexpr std::pair myPair{42, true};

  // constexpr can't be applied to regular function calls though - compilation error
  // constexpr int SomeValue{function_that_returns_int()};

  Resource<SomeValue> A;
  cout << "Resource A: " << A.val << endl;

  // use constexpr function
  constexpr int AnotherValue{get_int()};
  Resource<AnotherValue> B;
  cout << "Resource B: " << B.val << endl;

  cout << "Calling constexpr get_int() at runtime: " << get_int() << endl;

  constexpr int CompileTimeResult{get_another_int()};
  int RunTimeResult{get_another_int()};

  cout << "Compile time int: " << CompileTimeResult << endl;
  cout << "Run time int: " << RunTimeResult << endl;

  // the add function is evaluated at compile time, it is replaced with the result
  cout << "Consteval function result: " << Add(1, 2) << endl;

  return 0;
}