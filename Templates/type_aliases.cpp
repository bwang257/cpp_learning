/*
Introduction to type aliases
*/

// types get more and more verbose
// we use using to do this
// type aliases are defined in their scope 

#include <utility>
#include <iostream>
#include <string>
#include <type_traits>
#include "type_aliases.hpp"


using std::cout;
using std::endl;
using std::string;

struct Person {
  string name;
};

struct School {
  string name;
};

// create alias using using
// scoped same way as other declarations
using Student = std::pair<const Person&, const School&>;

void print_details(std::pair<const Person&, const School&> student){
  cout << "Student name: " << student.first.name << "\nSchool name: " << student.second.name << "\n";
}

// instead of using the preprocessor, we can implement conditional aliases
// using C++'s std::conditional, which accepts three template parameters
constexpr bool Use64BitInts{true};

// type given by type static member
using Integer2 = std::conditional<Use64BitInts, int64_t, int32_t>::type;
// or return resolved type directly
using Integer3 = std::conditional_t<Use64BitInts, int64_t, int32_t>;

// typedef is also supported in c++ (typdef int Integer;) but 
// using is preferred for readability and compatibility with templates

int main(){
  // a pair is a data type that allows you to store two objects in a single container
  std::pair<int, float> MyPair{9, 6.7f};
  cout << "First value: " << MyPair.first << "\nSecond value: " << MyPair.second << "\n";
  
  Person Brian{"Brian"};
  School WPI{"WPI"};

  // group together student and school
  // const simply says that the objects stored in the pair
  // cannot change, the objects themselves can change
  std::pair<const Person&, const School&> student1{Brian, WPI};
  print_details(student1);

  Person Andrew{"Andrew"};

  Student student2{Andrew, WPI};
  print_details(student2);

  // Use Integer alias defined in header file
  Integer newInteger;
  cout << "\nInteger size: " << sizeof(newInteger) << " bytes\n";

  // Use Integer2 alias defined conditionally
  Integer2 newInteger2;
  cout << "Integer2 size: " << sizeof(newInteger2) << " bytes" << endl;

  return 0;
}


