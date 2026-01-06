/*
Introduction to C++ 20 Concepts
*/
// resolves complexity and inelegance of SFINAE, with flexibility
// concepts set of requirements for types, allowing us to enforce type constraints
// without relying on SFINAE. Error messages are more readable and easier to understand
// error

#include <iostream>
#include <concepts>

// replace typename with concept
template <std::integral T>
T Average(T x, T y){
  std::cout << "Computing average between two integrals\n";
  return (x+y)/2;
}

template <std::floating_point T>
T Average(T x, T y){
  std::cout << "Computing average between two floating points\n";
  return (x+y)/2; 
}

// concept functions are perferred
template <typename T>
T Average(T x, T y){
  std::cout << "Calling generic average function\n";
  return x;
}

// requires keyword, allows for boolean logic
// can use type traits here but perferred to use a concept
// as they are designed for this (Ex. std::derived_from > std::base_of)
template <typename T>
  requires std::integral<T> || std::floating_point<T>
T Add(T x, T y){
  std::cout << "Adding values in function with \"requires\"\n";
  return x + y;
}

template <typename T>
T Add(T x, T y){
   std::cout << "Adding values in generic function\n";
   return x;
}

// trailing requires clause
// main use case is when we have a function that is not a template but is a member of a class or struct that is
template <typename T>
struct SomeContainer {
  void IntFunction()
    requires std::integral<T>
    {
      std::cout << "Calling int function\n";
    }
};

// abbreviated function template
// constraining auto parameters
auto revisedAverage(std::integral auto x, std::integral auto y){
  std::cout << "Calling revisedAverage\n";  
  return (x+y)/2;
}

// combined approaches
template <std::integral t1, typename t2>
  requires std::integral<t2> || std::floating_point<t2>
void Function2(t1 x, t2 y){
  std::cout << "Calling Function2\n";
}



int main(){

  // ex. std::integral (is integer?)
  if constexpr (std::integral<int>){
    std::cout << "An int is an integral\n"; 
  }

  // Constrained Template Parameters
  Average(3, 4);
  Average(3.14, 4.15);
  Average("Bob", "Jeff");

  // Requires keyword
  Add(static_cast<int>(3.14), 5);
  Add("Jeff", "Andrew");

  // Trailing Requires Clause
  SomeContainer<int> IntContainer;
  IntContainer.IntFunction();

  // Abbrieviated function template
  revisedAverage(3, 4);

  // combined approaches
  Function2(3, 6.31);

  return 0;
}
