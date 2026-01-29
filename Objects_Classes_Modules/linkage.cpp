/*
Internal and External Linkage
- compile using
g++ -std=c++17 linkage.cpp linkage2.cpp -o run
*/


// files --> compiler --> object files
// object files --> linker --> final, cohesive package


// identifiers we use are referred to as symbols with different types of linkage
// external -  available anywhere in the program, most global var, classes, structs, enums, free functions
// internal - only accessible in same file, commonly done through anonymous namespace
// no linkage - block scope

// one definition rule, no same identifier declared in same linkage
// most local definition of symbol used (it masks/shadows the other definition)


#include <iostream>
#include "linkage.hpp"

// anonymous namespace for internal linkage
// essentially creates a uniquely named namespace and then adds using 
// namespace __unique_compiler_name; in this file
namespace{
  void myfunc(){
    std::cout << "Myfunc with internal linkage called\n";
  }
}

void call_my_func(); // forward declaration, coould add extern here if preferred

extern const float Pi; // can also forward declare var with external linkage

int main(){

  myfunc(); // calls internal linkage
  call_my_func();
  std::cout << Pi << "\n";
  std::cout << Global << "\n";
}
