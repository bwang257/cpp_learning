/*
Introduction to overload resolution
*/

// Overloading allows multiple functions to have the same name, different parameter lists
// form of compile-time polymorphism, where the compiler determines function to call based on argument types
// known as overload resolution

/*
Steps:
Identifying candidate functions by name
Eliminating functions with the wrong number of parameters or parameters that can't be converted
Ranking the remaining functions based on the match between the arguments and parameters
Applying tiebreaker rules if there are multiple equally good matches
*/

// **default arguments are not considered (besides in second step)**
// only cares about implicit conversions possible
// can't go from string to int implicitly but can do std::stoi("42") as an argument

// if not one can be selected still, the compiler will determine the function call is too ambiguous, and throw an error.

// tie breakers:
// - nontemplate functions preferred
// - fewer steps prefered
// - template created by a concept preferred over general template

#include <iostream>

void print(int& x){
  std::cout << "Calling non-const int function" << std::endl;
}

// next tier down from exact candidates in the ranking are trivial conversions
// adding const for ex. is a trivial converstion
void print(const int& x){
  std::cout << "Calling const int function" << std::endl;
}

void print(double x){
  std::cout << "Calling double function" << std::endl;
}

template <typename T>
void print(T x){
  std::cout << "Template function called" << std::endl;
}

void testPrintShort(float x){
  std::cout << "float Function Called" << std::endl;
}

void testPrintShort(int x) {
  std::cout << "int Function Called" << std::endl;
}

struct Container{
  Container(int x){}
};

void testPrintInt(Container x){
  std::cout << "Container function called" << std::endl;
}

void testPrintInt(float x){
  std::cout << "Float function called" << std::endl;
}

void testPrintContainer(int& x){
  std::cout << "Int& function called" << std::endl;
}

void testPrintContainer(Container x){
  std::cout << "Container function called" << std::endl; 
}


// A requires 2 conversions to be a float, 1 to be an int
struct B {
  operator float() const { return 3.14f; }
};

struct A {
  operator int() const { return 42; }
  operator B() const { return {}; }
};


void PrintStruct(float x) {
  std::cout << "Called float overload" << std::endl;
}

void PrintStruct(int x) {
  std::cout << "Called int overload" << std::endl;
}

int SomeFunction(float x){
  std::cout << "Called float function that returns int" << std::endl;
  return 0;
}

float SomeFunction(int x){
  std::cout << "Called int function that returns float" << std::endl;
  return 1.2;
}


int main(){

  // candidates that require no argument conversion are at the top of rankings
  int y{42};
  print(y);
  print(42.0);
  print(42.0f);

  // C++ also has a list of perferred promotions
  // short/unsigned short --> int/unsigned int
  // float to double
  short x{42};
  testPrintShort(x);

  // built-in types perferred (float > container)
  int z{17};
  testPrintInt(17);

  // lowest ranked candidate functions include conversions
  // we define in classes and structs (ex. constructors and typecase operators)
  // since a const int can't be passed as a int&, we have to use the int -> container conversion
  // we define
  const int b{7};
  testPrintContainer(b);

  // fewer step conversions tiebreaker
  PrintStruct(A{});

  // Return Type is not considered 
  int test1{static_cast<int>(SomeFunction(42))};
  float test2{static_cast<float>(SomeFunction(42.0f))};
  return 0;
}