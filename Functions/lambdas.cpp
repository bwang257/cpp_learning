/*
Introduction to lambda function in c++
*/

// lambdas can be defined anywhere and can be anonymous with no name

// generally just use auto to define lambda, tricky to explicitly define

#include <iostream>
#include <utility>

void CallIfEven(int Num, auto Callback) {
  if (Num % 2 == 0) {
    Callback();
  }
}

int main() {
  // indicate lambda using [], need {} to initialize
  auto mylambda {[]{
    std::cout << "Lambda function 1 called\n";
  }};

  mylambda();

  // most common use for a lambda is to pass it to another function
  CallIfEven(4, []{
    std::cout << "The number was even\n";
  });

  // compiler infers return type
  auto mylambda2{[](int x){
    return x % 2 == 0;
  }};

  // but can explicitly specify 
  auto mylambda3{[](int x) -> bool {
    return x % 2 == 0;
  }};

  // need () if explicitly specifying
  auto mylambda4{[]() -> int {
    return 1;
  }};

  // lambdas do not have access to parent scope
  // relevant var have to be captured
  int x{1};
  int y{2};
  int z{3};

  [x, y, z] { 
    std::cout << "Sum: " << x + y + z << "\n";
  }();

  // modify captures: 
  [Value = x, Casted = static_cast<bool>(x)] {  
    std::cout << "Value: " << Value << '\n';
    std::cout << "Casted type: " << typeid(Casted).name() << "\n";
  }();

  // lambdas capture objects by const value, need mutable keyword
  // this is because lambdas are like functors, modifying a value will modifying the
  // lambda
  int Number{2};

  auto testLambda{[Number]() mutable {  
    std::cout << "Number in Lambda: " << ++Number << "\n";
  }};

  testLambda();
  testLambda();
  testLambda();
  std::cout << "Yet the value in main remains at " << Number << "\n";

  // instead can capture by refernece
  auto testLambda2{[&Number]() {  
    std::cout << "Number in Lambda: " << ++Number << "\n";
  }};
  testLambda2();

  // capture by const reference using <utility> function
  auto testLambda3{[&Number = std::as_const(Number)]() {  
    std::cout << "Number in Lambda: " << Number << "\n";
  }};
  testLambda3();

  // default captures
  [=] {std::cout << "Number now: " << Number << '\n'; }(); // capture all var we are using
  [&] {std::cout << "Modifying number: " << ++Number << '\n'; }(); // capture everything by reference

  // combine default captures
  // Capture x by reference
  // Capture y by const reference
  // Capture everything else by value
  [=, &x, &y = std::as_const(y)] {
    std::cout << "Sum: " << x + y + z << "\n";
  }(); 

  // can also add attributes such as [[deperecated]]
  // and [[nodiscard]] to enforce behaviors/warnigns at compile time
  auto Lambda4{[] [[deprecated("Oh no!")]] (int x, int y) -> int { return x + y; }
  };

  Lambda4(1, 2);
}