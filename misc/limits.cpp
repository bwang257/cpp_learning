// limits library + ranges for different data types

#include <limits>
#include <iostream>

void max_decimal_digits(){
  // recall a 32 bit int has 1 bit for the sign and 31 bits for magnitdue --> +/- 2.1 * 10^9
  // 32 bit float has 1 bit for the sign, 8 bits for the exponent, and 23 bits for the mantissa/fraction
  std::cout << "Max decimal digits for int: " << std::numeric_limits<int>::digits10 << "\n";
  std::cout << "Max decimal digits for float: " << std::numeric_limits<float>::digits10 << "\n";
  std::cout << "Max decimal digits for double: " << std::numeric_limits<double>::digits10 << "\n";
  std::cout << "Max decimal digits for long double: " << std::numeric_limits<long double>::digits10 << "\n";
  std::cout << "\n";
}

void max_values(){
  std::cout << "Max value for int: " << std::numeric_limits<int>::max() << "\n";
  std::cout << "Min value for int: " << std::numeric_limits<int>::min() << "\n";
  std::cout << "Max value for double: " << std::numeric_limits<double>::max() << "\n";
  std::cout << "Epsilon for float: " << std::numeric_limits<float>::epsilon() << "\n";

  // infinity
  if (std::numeric_limits<double>::has_infinity){
    double inf = std::numeric_limits<double>::infinity();
    std::cout << "Double infinity: " << inf << "\n";
  }
  std::cout << "\n";
}

int main(){
  max_decimal_digits();
  max_values();
}