/*
Lambda functions in c++
- captures
- closures - (functions that capture surrounding environment, take var by reference or value)

Compile with:
g++ -std=c++20 lambdas.cpp -o run
*/

// lambdas can be defined anywhere and can be anonymous with no name
// lambdas are just structs with an () operator


// generally just use auto to define lambda, tricky to explicitly define

#include <iostream>
#include <utility>
#include <memory>
#include <cassert>

struct myObj {
  void doWork(){
    std::cout << "MyObj is doing work!\n";
  }
};


void CallIfEven(int Num, auto Callback) {
  if (Num % 2 == 0) {
    Callback();
  }
}

// dangling reference hazard
auto make_bad_closure(){
  int local{5};
  return [&local](){return local; }; 
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

  // this can be applied to move semantics
  auto ptr = std::make_unique<myObj>();
  auto myObj_lam{[p = std::move(ptr)]{ p->doWork(); }}; 
  assert(!ptr); // null now
  myObj_lam();


  // instead can capture by reference, can be dangerous if the closure outlives the referenced var
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
  [=] {std::cout << "Number now: " << Number << '\n'; }(); // capture all var we are using by value
  [&] {std::cout << "Modifying number: " << ++Number << '\n'; }(); // capture everything by reference

  // mixed captures
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