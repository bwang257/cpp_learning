/*
Comprehensive intro to std::optional
*/

#include <iostream>
#include <optional>
#include <string>

class Student {
  public:
    std::string Name;
    std::optional<std::string> Employer;
};


// returning a null optional
std::optional<int> GetInt(){
  return std::nullopt;
}

// For use with or_else()
std::optional<int> GetDefaultValue(){ return std::optional<int>{1}; }

// For use with transform()
int Increment(int x){ return ++x; }
int Double(int x){ return x * 2; }

// For use with and_then()
std::optional<int> Log(std::optional<int> x){
  std::cout << "Value: " << x.value() << '\n';
  return x;
}

int main(){
  Student Brian{"Brian"};
  if (!Brian.Employer){ // std::optional implicityl converted to a bool, can also use .has_value()
    std::cout << "Brian has no employer\n";
  }

  // this is a nullable boolean, null just means absense of a value
  // implicit bool conversion of the optional evaluates to true regardless of the existing underlying val
  std::optional myBool{false};
  if (myBool){
    std::cout << "myBool has a value ...";
  }
  if (!myBool.value()){
    std::cout << "but its value is false\n";
  }

  // bad optional access
  std::optional<int> OptionalInt;
  try {
    OptionalInt.value();
  } catch (std::bad_optional_access& e){
    std::cout << "Caught an exception: " << e.what() << '\n';
  }

  std::cout << "Default value of OptionalInt: " << OptionalInt.value_or(0) << '\n';
  OptionalInt = 42;
  std::cout << "curr val of OptionalInt: " << *OptionalInt << '\n';
  OptionalInt.emplace(56); // can use for more complex objects
  std::cout << "curr val of OptionalInt: " << *OptionalInt << '\n';
  OptionalInt.reset();
  if (!OptionalInt.has_value()){
    std::cout << "OptionalInt no longer has a value after being reset\n";
  }

  // can directly use comparison operators
  // empty optional will always be != and < than other value
  OptionalInt = 12;
  if (OptionalInt == 12){
    std::cout << "OptionalInt is equal to 12\n";
  }
  OptionalInt.reset();
  if (OptionalInt != 12 && OptionalInt < -99999){
    std::cout << "OptionalInt is empty now\n";
  }

  if (!GetInt().has_value()) {
    std::cout << "Fuction returned a null optional\n";
  }

  // monadic operations c++23
  // or_else() - call the function if optional does not have a value
  // and_then() - return empty optional or invoke function
  // transform() - return empty optional or invoke function which will return a new value 
  std::optional<int> x;

  x.or_else(GetDefaultValue) // 1
   .transform(Increment) // 2
   .and_then(Log) // prints 2
   .transform(Double) // 4
   .and_then(Log); // prints 4
}





