/*
Introduction to throw, try, and catch and exception types
 */

// be aware of unreachable code when an exception is thrown
// execution of a throw is like a return, except a function exits without returning normally
// this can lead to memory leaks --> use smart pointers or try catch blocks

#include <iostream>


int main(){
  try {
    // can also throw other data types (bool, int, etc.)
    throw "some error";
    std::cout << "This is unreachable code\n";

  } catch (const char* e) { // catch string exceptions
    // don't need to add e variable
    std::cout << "Caught an error in catch(const char*): " << e << std::endl;
    
  } catch (...) {
    std::cout << "Caught an error in catch all statement catch(...)\n";
  }
  std::cout << "The program continuing: recovered sucessfully\n";
  return 0;
}