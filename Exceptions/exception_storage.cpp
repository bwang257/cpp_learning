/*
Exploration of where exceptions/thrown objects are stored

g++ exception_storage.cpp -o run

Showed that:
> Exceptions are stored in runtime-managed dynamic storage. Catch-by-value may create a stack-local copy. 
> throw e; copies from that local variable into a new dynamic exception object, not a stack exception object.
*/


#include <iostream>

static void print_stack_addr(const char* label){
  int local{};
  std::cout << label << ":   local = " << (void*)&local << '\n';
}

struct Probe {
  int val{42};

  Probe(){
    std::cout << "Probe constructor | this = " << (void*)this << '\n';
  }
  Probe(const Probe& other) : val{other.val} { 
    std::cout << "Probe copy constructor | this = " << (void*)this  << " | other = " << (void*)&other << '\n';
  }
  ~Probe(){
    std::cout << "Probe destructor | this = " << (void*)this << '\n'; 
  }
};


int main(){
  print_stack_addr("main");

  // puts highly performant for simple text output? but C++20 and above use std::print, std::println
  std::puts("\ncatch by reference:");
  try {
    print_stack_addr("before throw");
    throw Probe{};
  } catch (const Probe& p){
    print_stack_addr("catch ref");
    std::cout << "Caught ref:   &Probe = " << (void*)&p << '\n';
  }

  // copy elision can happen - compiler skips copying
  std::puts("\ncatch by value:");
  try {
    print_stack_addr("before throw");
    throw Probe{};
  } catch (const Probe& p){
    print_stack_addr("catch value");
    std::cout << "Caught value:   &Probe = " << (void*)&p << '\n';
  }

  try { 
    try {
      throw Probe{};
    } catch (Probe p){
      std::cout << "Caught inner value:   &Probe = " << (void*)&p <<  "   value = " << p.val << '\n';
      p.val = 999; // modify
      throw; // throw p throws a new exception object from the local catch var
    }
  } catch (const Probe& p){
    std::cout << "Caught outer ref:   &Probe = " << (void*)&p <<  "   value = " << p.val << '\n';
  }
}

