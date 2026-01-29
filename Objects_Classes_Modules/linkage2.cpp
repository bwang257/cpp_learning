/*
Supplemental file for linkage.cpp
*/

#include <iostream>
#include "linkage.hpp"


// float Pi{3.14f};
extern const float Pi{3.14f}; // const + constexpr var internal by default, need extern here

// define myfunc with external linkage
void myfunc(){
  std::cout << "Myfunc with external linkage called\n";
}

void call_my_func(){
  ::myfunc(); // calls the myfunc in external linkage/global scope
}