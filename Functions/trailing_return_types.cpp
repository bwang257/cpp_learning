/*
Discussion of trailing return types
*/

#include <iostream>

// use of trailing returns for all functions depends on
// team preferences

// compile-time error if there is a mismatch - binding declaration (unlike python)

// use of templates or auto requires the compiler to
// know exactly what the function should return or a return type
// as one of the parameters

// ex of using decltype
// note that const would go go before the arrow
// but override or final go after the trailing return type
template <typename T1, typename T2>
auto Multiply(T1 x, T2 y) -> decltype(x*y) {
  if (x == 0 || y == 0) {
    return decltype(x * y){0};
  }
  return x * y;
}

int main(){

  // allows order of args to not matter
  std::cout << "First: " << Multiply(2.1, 2) << "\n";
  std::cout << "Second: " << Multiply(2, 2.1) << "\n";

  auto ReturnValue{Multiply(0.0, 0.0)};
  std::cout << "Zero-Initialization: " << ReturnValue << " (" 
    << typeid(decltype(ReturnValue)).name() << ")\n";

}


