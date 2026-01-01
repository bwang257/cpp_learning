/*
Introduction to L-values and R-values
*/

#include <iostream>

using std::cout;
using std::endl;

// L-values (left values): expression that identifies a specific object or function
// can identify the address the l-value using &
// like containers

// R-values (rifght values): anything that is not an l-value (ex 42 is an r-value)
// can't do &42
// like contents of a container

// prvalue: expression the represents a value with no accessible identity or memory address
// typically intermediate or temporary

void someFunction(){}

// takes in a reference, non-const, can only take l-values
void l_value_reference(int& x){}

// takes in a reference, const, can take r-values
void l_value_reference2(const int& x){}


// int& is an l-value reference to an int
void anotherFunction(int& x){
  cout << "That was an l-value!\n";
}

// int&& is an r-value reference to an int
void anotherFunction(int&& x){
  cout << "That was an r-value!\n";
}


struct SomeType {
  // returns an instance of SomeType, temporary 
  SomeType operator+(int x){
    return SomeType{value + x};
  }
  
  // returns reference to existing location
  SomeType& operator++(){
    ++value;
    return *this;
  }
  int value = 0;
};

int main(){
  // create l-value Result that stores r-vlaue 1+5
  int Result{1+5};
  cout << "Result: " << &Result << endl;

  // this works because the compiler can implicitly convert 
  // an l-value to an r-value

  // can use an l-value where an r-value is expected
  int AnotherValue = Result;

  // functions are l-values
  cout << "someFunction: " << &someFunction << endl;

  // the result of a function can be an l or r-value
  // most cases, it would return an r-value (like an int)

  // logic also applied to operator functions
  // + returns r-value (prvalue)
  // ++ returns l-value
  SomeType st;
  cout << "++ operator function: " << &(++st) << endl;

  // can use r-value argument in reference parameter is const
  l_value_reference2(2);

  int x = 5;
  anotherFunction(x);
  anotherFunction(5);

  // a copy constructor accepts an l-value reference
  // considered more "important" than an r-value because it has a longer
  // lifespan


  // a move constructor accepts a r-value reference
  // considered less important, indicates we are free to just take control of its subresource
  // because the object is expiring soon anyway

  // std::move() casts an argument to an r-value reference, which can influence
  // what function is selected when that reference appears in the argument list

  // Resource x;
  // std::move(x) is the same as static_cast<Resource&&>(x)
}

