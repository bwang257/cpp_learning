/*
Discussion of variadic functions
*/

// key mechanism here is a function/template parameter packs
// denoted by ...

#include <iostream>
#include <tuple>
#include <type_traits>


template <typename T>
T myProcessingFunc(T val){
  if constexpr(std::is_arithmetic_v<T>){
    if (val % 2 == 0){
      return val/2;
    }
    return val + 1;
  }
  return val;
}

// can do const Types&&... , Types&
template <typename... Types>
void myFunc(Types... arguments){
  if constexpr(sizeof...(arguments) > 0){
    std::cout << "Received " << sizeof...(arguments) << " arguments\n";
    std::tuple<Types...> args{myProcessingFunc(arguments)...}; // arguments can be passed into a function first
    if (sizeof...(arguments) >= 3){
      std::cout << std::get<0>(args) << ", " << std::get<1>(args) << ", " << std::get<2>(args) << "\n";
    }
  } else {
      std::cout << "Parameter pack empty\n";
      return; // often code fails if arguments are empty, need to check at compile time
  }
}

// can force at least 1 arg (SFINAE)
template <typename T1, typename... types>
void myFunc2(T1 arg, types... args){
  std::cout << "Calling myFunc2\n";
}

// recursion with variadic logic
// technically this calls different functions 
// as the different templates have to be instantiated by
// the compiler. This can have performance issues if there is
// a lot of code
template <typename T1, typename... Types>
void Log(T1 First, Types... Others){
  std::cout << "Logging: " << First << '\n';
  if constexpr (sizeof...(Others) > 0) {
    std::cout << sizeof...(Others) << " Parameter(s) Remaining\n\n";
    Log(Others...);
  }
}

int main(){
  myFunc(133, 64, 21, true);
  myFunc();
  myFunc2(1);
  Log(42, 9.8, "Hello");

}