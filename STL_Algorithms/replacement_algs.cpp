/*
Discussion of the 4 common stl replacement algorithms
- every std alg here can accept a projection function as another arg
- can also use a iterator-sentinel pair instead of a range
- if we don't use ranges namespace, we must use iterator-iterator pair with no projection functions

g++ -std=c++20 replacement_algs.cpp -o run
*/

#include <algorithm>
#include <ranges>
#include <iostream>
#include <vector>


void print_vector(std::vector<int> vec){
  for (const int& val : vec){
    std::cout << val << ", ";
  }
  std::cout << "\n";
}

void stl_replace(){
  // std::ranges::replace
  // returns iterator pointing to sentinel
  std::vector Source{1, 2, 3, 3, 3, 3, 4, 5};
  std::cout << "Original: ";
  print_vector(Source);

  std::ranges::replace(Source, 3, 0);

  std::cout << "After Replace: ";
  print_vector(Source);
  std::cout << "\n";
}

void stl_replace_if(){
  // std::ranges::replace_if
  // also returns iterator to sentinel
  auto isEven{[](int x){return x % 2 == 0; }};
  std::vector nums{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::cout << "Original: ";
  print_vector(nums);

  std::ranges::replace_if(nums, isEven, 999);

  std::cout << "After Replace If: ";
  print_vector(nums);
  std::cout << "\n";
}

void stl_replace_copy(){
  // std::ranges::replace_copy
  // copies a range, but replaces certain objects with another
  // takes in source range, iterator to where to start copying, object to replace, object to replace with
  // returns struct with in (iterator to input sentinel) and out (iterator to 1 past end of ouput)
  std::vector Source{-1, 1, 2, 3, 3, 3, 6};
  std::vector<int> Destination;
  Destination.resize(Source.size());

  std::ranges::replace_copy(Source, Destination.begin(), 3, 0);

  std::cout << "Objects in Source: ";
  print_vector(Source);

  std::cout << "Objects in Destination: ";
  print_vector(Destination);
  std::cout << "\n";
}

void stl_replace_copy_if(){
  // std::ranges::replace_copy_if
  // takes in source range, iterator to where to start copying, predicate function, object to replace with
  // returns struct with in (iterator to input sentinel) and out (iterator to 1 past end of ouput)

  auto isOdd{[](int x){ return x % 2 == 1; }};

  std::vector Source{4, 1, 2, 3, 3, 3, 6};
  std::vector<int> Destination;
  Destination.resize(Source.size());

  std::ranges::replace_copy_if(Source, Destination.begin(), isOdd, 999);

  std::cout << "Objects in Source: ";
  print_vector(Source);

  std::cout << "Objects in Destination: ";
  print_vector(Destination);
  std::cout << "\n";
}

int main(){
  stl_replace();
  stl_replace_if();
  stl_replace_copy();
  stl_replace_copy_if();

}
