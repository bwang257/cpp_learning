


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


  // vector<int> mine;
  // std::cout << sizeof(mine) << '\n';
  // std::cout << mine.size() << '\n';
  // auto it = mine.cbegin();
  // std::cout << typeid(it).name() << '\n';
  // it++;


}