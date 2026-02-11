/*
User Defined Literals

g++ user_def_literals.cpp -o run
*/

// need _, stl libraries don't use an underscore
// implement using operator""_[literal](param type)
// can return any type we want
// values passed in must be positive but can override - operator
// should not be overused, be highly selective when using

#include <iostream>
#include <string>

// for const char* literals we can add parameter for size of string
void operator""_ip(const char* x, size_t size) {
  std::cout << "Called _ip with a string of size: " << size << "\n";
}


// can wrap literals in namespace to prevent naming conflicts
namespace distance_literals {
  // use case: conversions
  float operator""_mm(long double D){
    return D / 1000;
  }

  float operator""_cm(long double D){
    return D / 100;
  }

  float operator""_in(long double D){
    return D / 39.37;
  }

  float operator""_ft(long double D){
    return D / 3.28;
  }

  float operator""_m(long double D){
    return D;
  }

  float operator""_km(long double D){
    return D * 1000;
  }

  // can return custom types
  struct Distance {
    Distance(float Val) : Val{Val} {}
    float Val;
  };

  std::ostream& operator <<(std::ostream& Stream, Distance D){
    Stream << D.Val << " meters";
    return Stream;
  }

  Distance operator"" _miles(long double D){
    return Distance{float(D * 1609)};
  }

  // override - operator to work with negative values
  // for other examples, be careful of order of operations, 10C == 50F, -10 C != -50F
  Distance operator-(Distance D){
    std::cout << "Applying negation!\n";
    return Distance{-D.Val};
  }
}

int main(){
  using namespace distance_literals;
  float distance{3.0_m};
  std::cout << "Initial distance: " << distance << " meters\n";
  distance += 2.0_ft;
  std::cout << "New distance: " << distance << " meters\n";
  distance += 4.0_km;
  std::cout << "New distance: " << distance << " meters\n";

  // using custom return type:
  std::cout << 0.1_miles << " is equal to 0.1 miles\n";
  std::cout << -0.8_miles << " is equal to -0.8 miles\n";

}