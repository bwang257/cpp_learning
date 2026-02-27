/*
std::set in C++

g++ -std=c++14 sets.cpp -o run
*/


#include <iostream>
#include <set>
#include <cassert>


void lower_bound(){
  // the lower_bound fucntion returns interator pointing to first element
  // in the set that is not less than a specified value --> done using binary search
  std::set<int> s = {1, 3, 4, 5, 6, 7, 8, 9, 10};
  auto it = s.lower_bound(2); // log n
  assert(it != s.end() && *it == 3);
}

void erase(){
  // erase takes in iterator or value
  // returns iterator to the element immediately after the one that was removed
  std::set<int> s = {1, 3, 4, 5, 6, 7, 8, 9, 10};

  // example
  auto it = s.lower_bound(4);
  int upper_bound = 9;
  while (it != s.end() && *it <= upper_bound){
    it = s.erase(it);
  }
  assert(s.size() == 3); // just have 1, 3, 10
}


int main(){
  lower_bound();
  erase();

  std::cout << "All assertions passed\n";
}