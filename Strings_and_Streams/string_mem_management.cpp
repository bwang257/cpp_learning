/*
std::string memory management

g++ string_mem_management.cpp -o run
*/

// similar to std::vector


#include <iostream>
#include <string>


int main(){
  std::string my_str{" "};
  std::cout << "Curr size: " << my_str.size() << "\n";
  std::cout << "Curr capacity: " << my_str.capacity() << "\n";

  my_str.append(22, 'a');
  std::cout << "\nCurr size: " << my_str.size() << "\n";
  std::cout << "Curr capacity: " << my_str.capacity() << "\n";

  std::cout << "\nReserving 1000 chars:\n";
  my_str.reserve(1000);
  
  std::cout << "Curr capacity: " << my_str.capacity() << "\n";
  
  // shrink capacity, release surplus mem
  my_str.shrink_to_fit();
  std::cout << "\nCurr size: " << my_str.size() << "\n";
  std::cout << "Shrinked capacity: " << my_str.capacity() << "\n";

  // max size in curr environment
  std::cout << "\nMax size: " << my_str.max_size() << "\n";


  // resizing, fills in extra char as \0 by default
  std::string new_str{"Hello world"};
  new_str.resize(5);
  new_str.resize(10, '.'); // or specify character
  std::cout << "\n" << new_str << "\n";


}