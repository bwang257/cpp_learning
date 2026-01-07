/*
Exploration of size of different data types using sizeof operator
- compile using g++ -std=c++20 ./data_type_sizes.cpp -o run
*/

#include <iostream>
#include <concepts>
#include <string>
#include <vector>


class ArbClass {};
struct ArbStruct{};

class OneIntClass{ int x; };
class oneFunctionClass {
  public:
    int Print(){
      std::cout << "Something" << std::endl;
      return 1;
    }
};


void printVectorCapacityChanges(int max_size){
  int capacity = 0;
  int arb_value = 42;
  std::vector<int> v;
  std::cout << "=== Vector Capacity Doubles when Curr Capcity Exceeded ===\n";
  std::cout << "Elements: 0 | Capacity: " << v.capacity() << std::endl;
  for (int numElements = 1; numElements < max_size; numElements++){
    v.push_back(arb_value);
    int curr_capacity = v.capacity();
    if (curr_capacity != capacity){
      std::cout << "Elements: " << numElements << " | Capacity: " << curr_capacity << "\n";
      capacity = curr_capacity;
    }
  }
}

int main(){

  if constexpr(std::same_as<decltype(sizeof(int)), std::size_t>){
    std::cout << "\nNote: Type returned by sizeof() is std::size_t";
    std::size_t x{4};
    std::cout << "which is of size " << sizeof(x) << " bytes\n\n";
  }
  std::cout << "int: " << sizeof(int) << " bytes\n"; 
  std::cout << "double: " << sizeof(double) << " bytes\n";
  std::cout << "float: " << sizeof(float) << " bytes\n";
  std::cout << "empty string: " << sizeof(std::string) << " bytes\n";
  std::cout << "string of size 9: " << sizeof("123456789") << " bytes\n";

  // depends on system (modern macs are 64-bit systems, pointers are 64 bits/8 bits/byte -> 8 bytes)
  std::cout << "Pointer size: " << sizeof(int*) << " bytes\n"; 

  std::cout << "\n=== Vectors ===\n";
  // two size_t size and capacity values (8 bytes), 1 pointer double* (8 bytes)
  std::cout << "Size of a vector (struct): " << sizeof(std::vector<int>) << " bytes\n";

  // notes: 2 << 8 shifts bits of 2 to left by 8
  // 2 is 00000010. Shifting it left by 8 bits results in 00000010 00000000 (2 * 2^8 = 512)
  printVectorCapacityChanges(2 << 8);

  std::cout << "\n=== Classes and Structs ===\n";
  std::cout << "Empty class: " << sizeof(ArbClass) << " bytes\n";
  std::cout << "Empty struct: " << sizeof(ArbStruct) << " bytes\n";
  std::cout << "Class with 1 int: " << sizeof(OneIntClass) << " bytes\n";
  std::cout << "Class with 1 function: " << sizeof(oneFunctionClass) << " bytes\n";
  std::cout << std::endl;

}