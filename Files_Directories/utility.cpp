/*
Misc. Helper Functions for interactive filesystem.cpp 
*/

#include "utility.hpp"

int process_input(std::string input){
  try {
    return std::stoi(input);
  } catch (const std::exception& e){
    std::cerr << "Please enter integer choice\n";
    return 0;
  }
}