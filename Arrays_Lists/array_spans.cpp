/*
Introduction to Array Spans and std::span
*/

#include <iostream>
#include <span> // c++20 library
#include <cassert>
#include <vector>
#include <array>

// spans are a view, they do not onw the underlying elements
// minimal performance overhead

// a std::span is connected to a continguous block of memmory (lightweight interface, not copy)
// commonly used as a function parameter type
// solves issue of C-style arrays decaying to a pointer
void HandleValues(std::span<int> Values){
  std::cout << "Span Size: " << Values.size() << "\n";
}

// span templates
template <typename T>
void LogFirst(std::span<T> Values){
  std::cout << Values.front() << ",";
}

void HandleVector(std::vector<int> Vec){
  std::cout << "Vector Handled!\n";
}

int main(){
  // a std::span is connected to a C-style array (lightweight interface, not copy)
  int Values[]{1,2,3,4,5};
  HandleValues(Values);
  std::span Span{Values};
  std::cout << sizeof(Span) << " bytes\n";

  // can access points normally using [] and some static_array methods
  std::cout << "First value: " << Span.front() << "\n";
  std::cout << "Second value: " << Span[1] << "\n";
  std::cout << "Last value: " << Span.back() << "\n";

  // range based loop
  std::cout << "Range based loop\n";
  for (int x  : Span){ std::cout << x << ", "; }
  std::cout << "\n";

  // can also be used with vectors and arrays
  std::array arr{1, 2, 3, 4};
  std::vector vec(2, 5);
  HandleValues(arr);
  HandleValues(vec);

  // std::span::data returns c-style array
  // ptr to first element, not ethis technique creates a shallow copy of the array
  // array is not copied, just the ptr
  int* ptr = Span.data();
  std::cout << "Second element of Values: " << *(ptr+1) << std::endl;

  // create other container using span interators
  std::vector<int> other_vec {Span.begin(), Span.end()};
  HandleVector({Span.begin(), Span.end()});

  // subspans - just restricting view to a smaller set of elements
  std::span<int> first3{Span.first(3)};
  std::span<int> last3{Span.last(3)};
  // start at index 1, contain 3 elements
  std::span<int> last3{Span.subspan(1,3)};
  
}
