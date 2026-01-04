/*
Introduction to variable templates
*/

#include <iostream>

using std::cout;

const char nl = '\n';

// If we're defining a variable for pi, we may not know if
// users want a custom data type, double, float, etc.
// we need a different approach than just defining pifloat, pidouble, etc.

// Variable template
// this uses copy assignment (=) to allow narrowing casts
template <typename T>
constexpr T Pi = 3.141592653589793238462643383279;
// more explicitly
// template <typename T>
// constexpr T pi = static_cast<T>(3.141592653589793238462643383279);


template <int x, int y, int z>
constexpr int Calculation{(x*y)+z};

// we want to mark template variables as constexpr
// if we have multiple invocations of the same template variable (same arguments)
// modifying one will modify all
template <int x, int y>
int Result{x+y};

struct CustomType {
  constexpr CustomType(double value) : value{value} {}
  double value;
};


int main(){
  int IntPi{Pi<int>};
  cout << "Integer Pi: " << IntPi << nl;

  // custom type
  // when the compiler encounters a type it has not seen before
  // it calls the types constructor to construct CustomType Pi
  // Pi<CustomType> --> CustomType(3.1415....)
  auto Container{Pi<CustomType>};
  cout << "Container Value: " << Container.value << nl;

  // template calculations have no impact on performance
  int myCalc{Calculation<5, 3, 2>};
  cout << "Calculation result: " << myCalc << nl;

  // need for constexpr
  cout << "Current value of Result<1,2>: " << Result<1,2>++ << nl;
  int sum{Result<1,2>};
  cout << "New value of var created from Result<1,2>: " << sum << nl;

  // but Result is passed in as a copy, so modifying sum are not modifying Result<1,2>
  // they are acting on the copy
  sum++;
  cout << "New value of sum: " << sum << nl;
  cout << "Result<1,2> stays at: " << Result<1,2> << nl;



  return 0;
}