/*
Introduction to Functors
*/

// involves operator overloading
// have more functionality than simple function pointers
// can have same elements as classes

#include <iostream>

class Functor {
  public:
    Functor() = default;
  
    void operator()() {
      std::cout << "() called " << ++Invocations << " times\n"; 
    }
    // overload
    void operator()(int x, int y){
      std::cout << "() called to add sum: " << x + y << "\n";
      ++Invocations;
    }

    Functor( const Functor& source){
      std::cout << "Functor copied!\n";
    }

  private:
    int Invocations{0};
};

// using functors as first class functions
// functor is a function object that is known as a callable
// not really accurate to call it a function
// functions are callables but not all callables are functions
void callIfEven(int n, auto Func){
  if (n % 2 == 0){
    std::cout << "n is even so calling func: ";
    Func();
  }
}

void callIfEven2(int n, auto& Func){
  if (n % 2 == 0){
    std::cout << "n is even so calling reference func: ";
    Func();
  }
}



int main(){
  Functor(); // this simply instantiates the functor object
  Functor()(); // this calls the instantiated functor object
  Functor{}(); // better to do this instead
  Functor myFunc = Functor{};
  callIfEven(234, myFunc); // passed by value/copy by default
  myFunc(5, 7);

  // better to pass by reference
  callIfEven2(234, myFunc);

}