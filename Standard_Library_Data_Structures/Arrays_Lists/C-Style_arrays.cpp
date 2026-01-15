/*
Explorztion of older way to create arrays and why you should not use them
*/

#include <iostream>
#include <vector>

// solution could be to pass in the std::size_t length as an argument
void SomeFunc(int Array[]){
  std::cout << "The size of the array is now " << sizeof(Array) << " bytes?!\n";
}


int main(){
  int x[5];
  int y[5]{1, 2, 3, 4, 5};
  int z[]{1, 2, 3, 4, 5}; // let compiler deduce length
  std::cout << "Size of array with " << std::size(x) << "elements: " << sizeof(x) << " bytes\n";
  
  // issue is c-style arrays decay to a pointer to the first element of the array
  SomeFunc(x);

  // std::memcpy() copies bytes from one memory location to another
  // takes in ptr to new loc, ptr to old loc, and num bytes to copy
  // just use std::vector to do this automatically
  int a[6];
  std::memcpy(a, y, sizeof(y));
  a[5] = 6;
  std::cout << "a values: ";
  for (auto i : a){std::cout << i << ", "; }
  std::cout << std::endl;

  // converting to other containers
  // accepts 2 iterators and cpies everything from the first to the second
  // can be expensive
  std::cout << "Vec values: ";
  std::vector<int> Vec{a, a+6};
  for (auto i : Vec){std::cout << i << ", "; }
  std::cout << std::endl;

}