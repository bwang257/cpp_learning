/*
Introduction to the 8 main searching algorithms in the C++ stdlib

Compile with: g++ -std=c++20 search.cpp -o run
*/

#include <algorithm>
#include <iostream>
#include <vector>


struct CustomType{
  int value;
  bool operator==(const CustomType& other) const {
    return value == other.value;
  }
};


// 1
void find_algorithm(){
  // std::ranges::find
  // able to use with ranges, iterator/sentinal ranges, custom types
  // and projection functions. Returns first occurence

  // ex with iterators, custom type + projection function, overloaded  == operator in struct
  std::vector vec{CustomType{1}, CustomType{2}, CustomType{-3}, CustomType{3}, CustomType{5}};

  auto Projector{[](CustomType& x){ return CustomType(abs(x.value)); }};

  auto result{std::ranges::find(vec.begin(), vec.end(), CustomType{3}, Projector)};
  std::cout << "Found a struct with val " << result->value << " in position "<< std::distance(vec.begin(), result) << "\n";

  auto result2{std::ranges::find(vec.begin(), vec.end(), CustomType{6}, Projector)};
  if (result2 == vec.end()){
    std::cout << "A struct with val 6 or -6 was not found in the vector. Not safe to dereference\n";
  }
}

// 2
void find_if_algorithm(){
  // std::ranges::find_if
  // doesn't use == but passes each object into a predicate function we provide
  // also returns end iterator if does not find anything
  std::vector vec{CustomType{1}, CustomType{2}, CustomType{-3}, CustomType{4}, CustomType{5}};
  auto isEven{[](CustomType& x) { return x.value % 2 == 0; }};
  auto Result{std::ranges::find_if(vec, isEven)};
  auto Result2{std::ranges::find_if(Result+1, vec.end(), isEven)};
  
  std::cout << "Found an even struct with val " << Result->value  << " in position " << std::distance(vec.begin(), Result) << "\n";
  std::cout << "Found another even struct afterwards with val " << Result2->value  << " in position " << std::distance(vec.begin(), Result2) << "\n";
}

// 3
void find_if_not(){

}

int main(){
  // find_algorithm();
  // find_if_algorithm();
  find_if_algorithm();

}