/*
Header file for template_specialization.cpp showcasing
template specialization with libraries
*/
#pragma once
#include <iostream>

namespace SomeLibrary {
  template <typename T>
  std::string GetName(T& Obj){
    return Obj.GetName();
  }
  
  template <typename T>
  void Process(T& Obj){
    std::cout << "Finished processing " << GetName(Obj) << std::endl;
  }
}
