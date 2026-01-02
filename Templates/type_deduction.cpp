/*
Introduction to tools for compile-type type deduction
  - decltype
  - std::declval
*/

// We might not know a type ahead of time
// this is where we can use the compilter's type deduction

// decltype asks the compiler what is the type of this expression
// **doesn't evaluate the expression**

// std::declval allows up to work with a hypothetical instance
// as decltype can be cumbersome if the expression requires
// constructing an object with complex constructor arguments

#include <iostream>
#include <utility>


using std::cout;

struct mysteriousStruct {
  mysteriousStruct(int val1, int val2, int val3) : field1(val1), field2(val2), field3(val3) {}
  int function2(){return 2;}
  int field1;
  int field2;
  int field3;
};


int function1(){return 1;}

int main(){
  
  // can use decltype wherever a is expected
  using SomeType = decltype(42);
  SomeType someValue;

  decltype(function1()) anotherValue;

  // decltype limitations ise an object needs to be constructed
  // arbitrary constructor arguments may need to be added
  // gets worse when we won't even know what type we're constructing + constructor arguments
  using SomeType2 = decltype(mysteriousStruct{1, 2, 99}.function2());

  // std::declval works with a hypothetical object
  using someType3 = decltype(std::declval<mysteriousStruct>().function2());


  return 0;
}

