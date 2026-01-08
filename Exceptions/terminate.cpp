/*
*/


#include <exception>
#include <iostream>
#include <vector>

// std::terminate() calls another function std::abort() to close our app
// can pass a function in (note porgramming paradigm first-class functions) to customize
void CustomTerminate(){
  std::cout << "Terminating\n" << std::flush; // abort does not flush the buffer
  std::abort();
}

void terminateFunction(){
  std::set_terminate(CustomTerminate);
  std::terminate();
  std::cout << "Blah blah blah\n";
}


// noexcept specifier states that no exceptions thrown
// and no exception will thrown will be handled internally, without leaking up to the caller
// enforced at runtime. if exceptin leaked --> std::terminate will be called
void someFunction() noexcept {}

// noexcept can be conditional too but the boolean must be evaluated at compile time
constexpr bool SomeBoolean{true};
void AnotherFunction() noexcept(SomeBoolean) {}

struct MyType {
  MyType() = default;
  MyType(const MyType& Other) {
    std::cout << "MyType Copy Constructor\n";
  }

  MyType(MyType&& Other) {
    std::cout << "MyType Move Constructor\n";
  }
};

struct MyOtherType {
  MyOtherType() = default;
  MyOtherType(const MyOtherType& Other) {
    std::cout << "MyOtherType Copy Constructor\n";
  }

  MyOtherType(MyOtherType&& Other) noexcept(true) {
    std::cout << "MyOtherType Move Constructor\n";
  }
};


int main(){
  // terminateFunction();

  // recall move semantics
  // if exception is thrown during move process, both objects are in indeterminate state
  // std::move_if_noexcept() will only case our object to an rvalue ref if move constructor is noexcept
  MyType Orig;
  MyType New{std::move_if_noexcept(Orig)}; // calls copy instructor;
  MyOtherType Orig2;
  MyOtherType New2{std::move_if_noexcept(Orig2)}; // calls move instructor;

  // noexcept is used for data structures and algorithms too
  // std::vector calls move_if_noexcept when resizing

  // prompt vector to move to new location using reserve()
  // we can see this
  std::cout << "\nWith Vectors:\n";
  std::vector <MyType> V;
  V.emplace_back(); // add new elements to end with default constructor
  V.reserve(100);

  std::vector <MyOtherType> V2;
  V2.emplace_back();
  V2.reserve(100);
}

