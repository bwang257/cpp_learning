/*
Introduction to templates and header files
- main code for this topic in the hpp and ipp files
*/

#include <iostream>
#include "template_headers.hpp"


int main(){
  Pair<int, float> myPair{4, 6.7f};
  // call implementation defined in template_headers.ipp
  myPair.get_first();
  myPair.get_second();
  return 0;
}