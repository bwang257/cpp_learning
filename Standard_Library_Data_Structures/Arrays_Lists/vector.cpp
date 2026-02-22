/*
Notes on std::vector

g++ -std=c++23 vector.cpp -o run
*/

#include <iostream>
#include <vector>

void print_vector(const std::vector<int>&);

void insertion(){
  // instead of pushing back multiple times (which can cause the vector to resize)
  // insert can calculate total extra memory needed and resize accordingly

  // insert member function takes a position iterator, 
  // start of range, and end of range
  std::vector<int> vec{0, 1, 2, 3, 4, 5, 6}; 
  vec.insert(vec.begin(), -1);

  std::vector<int> vec2{7, 8, 9, 10};
  vec.insert(vec.end(), vec2.begin(), vec2.end());
  print_vector(vec);

  // c++23 allows for insert range, which just takes the position iterator and **any** range
  std::vector<int> vec3{99, 42, 33};
  vec.insert_range(vec.begin() + 4, vec3); // insertion occurs before this position
  print_vector(vec);

  std::cout << "\n";
}

int main(){
  insertion();
}

void print_vector(const std::vector<int>& vec){
  for(const auto& num : vec) std::cout << num << ", ";
  std::cout << "\n";
}



