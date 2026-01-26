/*
Iterator and range-based sort algorithms
*/

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>


int main(){
  // note algorithm container requriements for these algorithms
  // ex. std::ranges::sort() and std::sort() require our range or iterators
  // to support random access. also require comparable elements
  // also must note algorithm preconditions that leads to incorrect behavior 
  // rather than compiler error

  std::vector<int> vec1 = {1, 5, 3, 7, 2, 3};
  std::ranges::sort(vec1, [](int a, int b){return a > b;});
  for (auto x : vec1){
    std::cout << x << ", ";
  }
  std::cout << "\n";

  // often we can use functors instead from teh std::ranges like std::ranges::greater
  std::vector<std::string> vec2 = {"apple", "banana", "apple", "cherry", "apple"};
  std::ranges::sort(vec2, std::ranges::less{});
  for (auto x : vec2){
    std::cout << x << ", ";
  }
  std::cout << "\n";
}