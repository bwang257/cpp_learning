/*
Exploration of std lib tuples
*/

// heterogenous containers storing any number of elements

#include <iostream>
#include <tuple>
#include <format>

// tuple type traits
template <typename T>
void HandleTuple(T tuple){
  std::cout << "Size of tuple: " << std::tuple_size_v<T> << '\n';
  if constexpr (std::is_same_v< std::tuple_element_t<0, T>, float>) {
    std::cout <<"The first element is a float\n";
  }
}

int main(){
  // create a tuple
  std::tuple<float, bool, int> mytuple{9.8f, true, 7};
  std::tuple mytuple2{std::make_tuple(9.8f, false, 87)}; // CTAD

  // can do <0> or <float> (if only one float in the tuple)
  if constexpr (std::same_as<decltype(std::get<0>(mytuple)), float&>){
    std::cout << "std::get function returns a references to the element\n";
  }

  // structured binding
  auto [a, b, c]{mytuple};
  std::cout << std::format("mytuple contained: {} {} {}\n", a, b, c);

  // use std::tie to redefine structured binding var
  std::tie(a, b, c) = mytuple;
  
  // std::ignore to not change a var
  std::tie(a, std::ignore, c) = mytuple;
  std::cout << std::format("a, b, c now: {} {} {}\n", a, b, c);

  // print tuple information
  HandleTuple(mytuple);

  // tuple concatenation (tuples can't be resized but can be concatenated)
  std::tuple<int, float, double> orig{1, 2.0f, 3.01};
  std::cout << "size of a int, float, double tuple " << sizeof(orig) << "\n";
  std::tuple<int, float, double> additions{4, 5.0f, 6.01};
  auto newTuple{std::tuple_cat(orig, additions)};
  std::cout << "size of 2 concatenated int, float, double tuples " << sizeof(newTuple) << "\n";
  HandleTuple(newTuple);
  // C++ has limited support for iteration across heterogeneous contaners
  // Will learn more advanced topics later
}