/*
Discussion of STL Copying algorithms
- you can do an iterator-sentinel pair for all these algorithms instead of using a range
- can also omit ranges namespace if needed: std::ranges::copy --> std::copy (but need to use iterator-iterator pair with no projection functions)
*/

#include <algorithm>
#include <iostream>
#include <ranges>
#include <vector>


void stl_copy(){
  // std::ranges::copy
  // takes in source range and iterator to where to begin copying elements
  // returns struct with in (where input sentinel encountered) and out (iterator to beyond last element copied)
  // use if copying to the left
  std::vector Source{1, 2, 3};
  std::vector Destination{0, 0, 0, 0, 0, 0};

  std::ranges::copy_result Result{std::ranges::copy(Source, Destination.begin())};

  int64_t InputSize{std::distance(Source.begin(), Result.in)};

  std::cout << "The input size was " << InputSize << "\n";
  
  for (auto i : Destination) {
    std::cout << i << ", ";
  }
  std::cout << "\n";
}

void stl_copy_backwards(){
  // std::ranges::copy_backwards
  // takes in source range and iterator to where to finish copying elements
  // same returns struct with in (iterator to sentinel trigger) and out (iterator pointing to the last element moved)
  // use if copying to the right
  std::vector Source{1, 2, 3};
  std::vector Destination{0, 0, 0, 0, 0, 0};

  std::ranges::copy_backward(Source, Destination.end());

  for (auto i : Destination) {
    std::cout << i << ", ";
  }
  std::cout << "\n";

}

void stl_reverse_copy(){
  // std::ranges::reverse_copy
  // same as copy but the elements copied in reverse order
  std::vector Source{1, 2, 3};
  std::vector Destination{0, 0, 0, 0, 0, 0};

  std::ranges::reverse_copy(Source, Destination.begin());

  for (auto i : Destination) {
    std::cout << i << ", ";
  }
  std::cout << "\n";
}

void stl_rotate_copy(){
  // std::ranges::rotate_copy
  // takes in source range, iterator to object to start copying with, and where to start copying in destination range
  // returns stryct with in (where sentinel encountered) and out (iterator pointing beyond last element copied in output location)
  std::vector Source{1, 2, 3, 4, 5, 6};
  std::vector Destination{0, 0, 0, 0, 0, 0};

  std::ranges::rotate_copy(Source, Source.end() - 1, Destination.begin());

  std::cout << "-----Source: ";
  for (auto i : Source) {
    std::cout << i << ", ";
  }

  std::cout << "\nDestination: ";
  for (auto i : Destination) {
    std::cout << i << ", ";
  }
  std::cout << "\n";
}

void stl_copy_n(){
  // std::Ranges::copy_n
  // copy the first n objects starting with an input range iterator to the output range iterator
  std::vector Source{1, 2, 3, 4, 5, 6};
  std::vector Destination{0, 0, 0, 0, 0, 0};

  auto [in, out]{std::ranges::copy_n(Source.begin(), 4, Destination.begin())};

  std::cout << "Values in Destination: ";
  for (auto& Num : Destination) {
    std::cout << Num << ", ";
  }
  std::cout << "\n";
}


void stl_copy_if(){
  // std::ranges::copy_if
  // accepts predicate function
  // returns struct with in (where sentinel was encountered in input range) and out (iterator beyond last element copied)
  // can also take in a projection function as an optional 4th arg. 
  std::vector Source{1, 2, 3, 4, 5, 6};
  std::vector<int> Destination;
  Destination.resize(Source.size());

  auto isEven{[](const int& x) { return x % 2 == 0; }};

  std::ranges::copy_if(Source, Destination.begin(), isEven);

  std::cout << "-----Source: ";
  for (auto i : Source) {
    std::cout << i << ", ";
  }

  std::cout << "\nDestination: ";
  for (auto i : Destination) {
    std::cout << i << ", ";
  }
  std::cout << "\n";
}


bool AbsEquals(int x, int y){
  return std::abs(x) == std::abs(y);
}

void stl_unique_copy(){
  // std::ranges::unique_copy
  // will only remove consecutive duplicates, not duplicates globally
  // to get truly unique values, you will need to sort the range first
  // can take in third arg for a custom comparison function
  std::vector Source{1, -1, -2, 1, 2, 2, 2, 2};
  std::vector<int> Destination;
  Destination.resize(Source.size());

  std::ranges::unique_copy(Source, Destination.begin(), AbsEquals);

  std::cout << "-----Source: ";
  for (auto i : Source) {
    std::cout << i << ", ";
  }

  std::cout << "\nDestination: ";
  for (auto i : Destination) {
    std::cout << i << ", ";
  }
  std::cout << "\n";
}


int main(){
  stl_copy();
  stl_copy_backwards();
  stl_reverse_copy();
  stl_rotate_copy();
  stl_copy_n();
  stl_copy_if();
  stl_unique_copy();
}