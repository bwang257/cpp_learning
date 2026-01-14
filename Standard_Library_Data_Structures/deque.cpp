/*
Introduction to std::deque
*/


// replicates abilities of dynamic arrays
// compared to arrays, faster at resizing, adding and removing
// objects at arbitrary locations. More memory needed, 
// and slower at accessing arbitrary elements using []

#include <iostream>
#include <deque>
#include <vector>

// iteration
void printInfo(std::deque<int>& dq){
  std::cout << "Current " << dq.size() << " values: ";
  for (auto i : dq){
    std::cout << i << ", ";
  }
  std::cout << '\n';
}


int main(){
  std::vector<int> vec{6, 7, 8, 9, 10};
  std::vector<int> vec2{-5, -4, -3, -2, -1, 0};

  // methods of initializing
  std::deque<int> dq{1, 2, 3, 4, 5};
  std::deque<int> dq2{vec.begin(), vec.end()};

  // c++23
  dq.append_range(vec); // to the back of the deque
  dq.prepend_range(vec2); // to the front of the deque
  std::deque<int> dq3{std::from_range, vec}; // from_range here is a disambiguation token
  
  printInfo(dq);

  // getting elements: .front(), .back(), [], .at() (but most compilers perform bounds checking anyway during dev)
  // adding elements: emplace/push_front(), emplace/push_back()
  // removing elements: pop_front(), pop_back()

  // erasing arbitrary elements done through iterators
  auto Iterator4 {dq.begin() + 3};
  std::cout << "Removing -2 from the deque\n";
  dq.erase(Iterator4);
  printInfo(dq);

  auto Iterator6{dq.begin()+5};
  auto Iterator11{dq.begin()+10};
  std::cout << "Removing 1-5 from the deque\n";
  dq.erase(Iterator6, Iterator11);
  printInfo(dq);

  // inserting at any position
  // emplace take in iterator, plus consturctor arguments
  // insertion occurs before the iterator
  Iterator6 = dq.begin()+5;
  std::cout << "Inserting a 3 before " << *Iterator6 << "\n";
  dq.emplace(Iterator6, 3);
  printInfo(dq);

  // insert, note insert_range(iterator, range)
  std::cout << "Inserting a 5 before " << *Iterator6 << "\n";
  dq.insert(Iterator6, 5);
  printInfo(dq);

  std::cout << "Inserting 5 0's before -4\n";
  dq.insert(dq.begin()+1, 5, 0);
  printInfo(dq);

  // replace contents 
  dq.assign({6, 7, 8}); 
  printInfo(dq);
  dq.assign(5, 2); // or 5 copies of 2
  printInfo(dq);

  std::vector replacements{1, 42, 67};
  dq.assign_range(replacements);
  printInfo(dq);

  dq.clear();
  if (dq.empty()){ std::cout << "The deque is now empty!\n"; }

  // most efficient way of switching content of two deque objects
  std::deque A{1, 2, 3};
  std::deque B{4, 5, 6};

  A.swap(B);
  std::cout << "A Values: ";
  for (int x : A) { std::cout << x << ", "; }
  std::cout << "\n";

  std::cout << "B Values: ";
  for (int x : B) { std::cout << x << ", "; }
  std::cout << "\n";


  // memory management

  // resize used for when an algorithm perhaps needs to copy objects from
  // on loc to another and assumes that the deque has enough capacity
  std::deque mydq{1, 2, 3};
  mydq.resize(1); // cuts off 
  printInfo(mydq);

  mydq.resize(5, 10); // default construct additional values, unless another default specified (ex. 10)
  printInfo(mydq);

  std::cout << "Size: " << mydq.size() << "\n";
  std::cout << "Max size: " << mydq.max_size() << "\n";

  // generally std::deque very efficient and will shrink any memory it is not using
  // but in memory-constrained environments, can call

  mydq.pop_back();
  size_t initial = sizeof(mydq);
  std::cout << "Curr memory size: " << initial << "\n";
  mydq.shrink_to_fit();
  size_t fin = sizeof(mydq);
  std::cout << "Memory size after shrinking to fit: " << fin << "\n";
  if (fin == initial){ std::cout << "As you can see, memory management with std::deque if very proactive and almost never required.\n"; }




  

  // .front, .back



}