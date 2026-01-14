/*
Introduction to std::stack
*/

#include <iostream>
#include <stack>
#include <vector>

// a std::stack is also a container adaptor
// default is a std::deque for the underlying container
// underlying container just needs to implement certain list of methods

int main(){
  std::vector<int> Nums{1, 2, 3, 4, 5};
  std::stack Stack{Nums.begin(), Nums.end()};
  std::cout << "Current top of the stack: " << Stack.top() << "\n";
  Stack.pop();
  std::cout << "Now the top of the stack is: " << Stack.top() << '\n';

  // inserting elements
  Stack.emplace(6);
  Stack.push(7);

  std::vector vec{8, 9, 10};
  Stack.push_range(vec); // c++23 concept
  std::cout << "The top of the stack is now: " << Stack.top() << '\n';

  while (!Stack.empty()){
    std::cout << Stack.top() << ", ";
    Stack.pop();
  }
  std::cout << "\n";
}
