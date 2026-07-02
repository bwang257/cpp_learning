


/*
g++ std_vector.cpp -o run
*/
#include <iostream>
#include <vector>
#include "std_vector.hpp"


#include <typeinfo>


int main(){
  std::vector<int> test;
  std::cout << sizeof(test) << " bytes\n";
  for (int idx{}; idx < 10; idx++){
    std::cout << test.capacity() << '\n';
    test.push_back(idx);
  }

  // auto it = test.begin();
  // auto it2 = it + 1;
  // std::cout << &(*it) - &(*it2) << '\n';
  // std::cout << it2 - it << '\n';
  // std::cout << "WOW: " << *it2 << '\n';


  vector<int> mine;
  std::cout << sizeof(mine) << '\n';
  int add = 1;
  mine.push_back(add);
  mine.push_back(add);
  std::cout << "Initial capacity: " << mine.capacity() << '\n';
  mine.reserve(1000);
  std::cout << "New capacity: " << mine.capacity() << '\n';

}