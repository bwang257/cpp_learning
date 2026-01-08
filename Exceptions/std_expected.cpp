/*
Introduction to errors as values and std::expected
*/

#include <iostream>
#include <expected> // C++23 introduced std::expected
#include <string>

// exceptions can be computationally expensive and can lead to 
// complex control flow
// some projects completely disable exceptions


// a simple way around exceptions is to return values as error codes or a complex type
// 0: ran successfully
// 1: error occured

// std::pair<int, bool> res = Divide(4, 0);

// struct DivisionResult {
//   int Result;
//   bool wasSuccessful; 
// }

// out parameters
bool Divide(int a, int b, int& Result){
  if (b==0) return false;
  Result = a/b;
  return true;
}

// first type is expected, second type returned if an error occurs
// can use void as the expected type
using DivisionResult = std::expected<int, std::string>;

DivisionResult Divide(int a, int b){
  if (b==0){
    return std::unexpected<std::string>{"Cannot divide by zero"}; // don't need <std::string> --> CTAD
  
  }
  // std::expected<T, E> has constructor that accepts a T
  return a/b;
}

DivisionResult Log(const DivisionResult& x){
  std::cout << "Value: " << x.value() << '\n';
  return x;
}

DivisionResult LogError(const std::string& x){
  std::cout << "The issue was: " << x << '\n';
  std::cout << "Using a default value 0: "<< '\n';
  return 0; // returns DivisionResult{0}
}

int Increment(int x){
  std::cout << "Incrementing\n";
  return ++x;
}

std::string FormatErrorMessage(const std::string& error){
  return "Division Failed: " + error + '\n';
}

std::string Stringify(int x){
  return std::to_string(x);
}

std::expected<int, std::string> giveUnexpected(){
  return std::unexpected{"Oh No."};
}


int main(){
  int res;
  if (Divide(4, 2, res)){
    std::cout <<"Division was successful and the answer was " << res << std::endl;
  }

  DivisionResult ResultA{Divide(0, 5)};
  DivisionResult ResultB{Divide(5, 0)};

  // use has_value or bool operator
  if (ResultA){
    // returned std:expected is like a pointer to the result if it was a success
    std::cout << ResultA.error_or("Success: ") << "0 / 5 Succeeded: " << *ResultA <<  "\n";
  }
  if (ResultB.has_value()) {
    std::cout << ResultB.error_or("Success: ") << "5 / 0 Succeeded: "<< ResultB.value() <<  "\n";;
  } else {
    std::cout << "5 / 0 Failed: " << ResultB.error() << "\n";
  }

  // can do equality comparisons
  // from C++20,compilers automatically implement != from ==, no need to override it
  // A != B --> !(A==B)
  if (ResultA == 0 && ResultB == std::unexpected{"Cannot divide by zero"}){
    std::cout << "Equality comparisons succeeded\n";
  }

  // value_or sets a default value if the division failed
  int Result{Divide(10, 0).value_or(1)};
  std::cout << "Using value: " << Result << "\n";

  // monadic operations for chaining
  Divide(10, 5).and_then(Log);
  Divide(10, 0).and_then(Log); // this will not log 
  Divide(10, 0).or_else(LogError).and_then(Log); 
  // transform modifies expected value if the std::expected is in the expected state
  Divide(10, 5).and_then(Log).transform(Increment).and_then(Log);
  // transform error modifies the error value
  Divide(10, 0).transform_error(FormatErrorMessage).or_else(LogError).and_then(Log).transform(Increment).and_then(Log); 

  // more complex pipelines can be built as transform() and transform_error() can return a different
  // type than their inputs
  std::string NewResult{Divide(2,0).or_else(LogError).transform(Stringify).value()};
  std::cout << "Result: " << NewResult << std::endl;


  // if still using exceptions, exception thrown when .value() taken on std::unexpected
  try {
    giveUnexpected().value();
  } catch (std::bad_expected_access<std::string>& E){
    std::cout << E.what() << ": " << E.error() << '\n';
  }

}
