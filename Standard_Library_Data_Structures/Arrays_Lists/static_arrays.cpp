/*
Introduction to static arrays using std::array
*/

#include <iostream>
#include <array>

// arrays are a contiguous block of memory
// size must be known at compile time

std::size_t CalculateIndex(){
  // can be used as arrays can store more values
  // than the max size of an int. deal with that using std::size_t
  std::size_t x = 5;
  return x;
}

int main(){
  std::array<int, 5> myArray;
  std::cout << "Allocated size of a 5 int array: " << sizeof(myArray) << " bytes" << std::endl;

  try {
    // unlike [], .at() has bounds checking (at a perforamnce cost)
    // [] out of range behavior is unpredicable, often results in crash
    myArray.at(5);
  } catch (std::out_of_range& e){
    std::cout << "Out of range error: " << e.what() << "\n";
  }
  
  std::cout << "\n=== Methods ===\n";
  std::array myArray2{ 1,2,3,4,5 }; // note Class Template Argument Deduction
  std::cout << "Front: " << myArray2.front() << "\n";
  std::cout << "Back: " << myArray2.back() << "\n";
  std::cout << "Size: " << myArray2.size() << "\n";
  std::cout << "For Loop: ";
  for (std::size_t i{0}; i < myArray2.size(); ++i){
    std::cout << myArray2[i] << ", ";
  }
  std::cout << "\nRange-based For Loop: ";
  for (int& num : myArray2){
    std::cout << num << " | ";
  }
  // Static Array funnctions return references allowing assignment using = and updating objects
  static_assert((std::same_as<decltype(myArray2.front()), int&>));
  static_assert((std::same_as<decltype(myArray2[1]), int&>));

  // multidimensional array
  using Grid = std::array<std::array<int, 3>, 3>;
  Grid myGrid {
    {
      {1,2,3},
      {4,5,6},
      {7,8,9}
    }};
  std::cout << "\n3x3 grid center: " << myGrid[1][1] << "\n";
  
}
