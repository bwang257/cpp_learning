/*
Introduction to creating our own test types
*/

#include <concepts>
#include <iostream>
#include <string>

// basic concept structure
template <typename T> // cannot reference other concepts
// expression that we want to return true/false
concept myNumberConcept = 
  std::integral<T> || std::floating_point<T>;

// ex.
template <myNumberConcept T>
void ConstrainedTemplate(T x) {
  std::cout << "That's an number\n";
}

template <myNumberConcept T>
void UnConstrainedTemplate(T x){
  std::cout << "That's an number too\n";
}

// use of requires for more complex expressions
// ex. covertible to and from an int
template <typename T>
concept ConvertibleToFromInt = requires {
  requires std::convertible_to<int, T>;
  requires std::convertible_to<T, int>;
  // cannot just write std::... --> concept needs to be valid, not just true/false
};

template <ConvertibleToFromInt T>
void myFunction(T x){
  std::cout << x << " is convertible to an int\n";
}

template <typename T>
void myFunction(T x){
  std::cout << "Input is not convertible to an int\n";
}

// more complex
struct SomeType {
  SomeType(int x) : value{x} {};
  int value;
  operator int() { return value; };
};

template <typename T>
concept IntOrFloatClass = std::is_class_v<T> &&
  requires {
    requires std::convertible_to<int, T>;
    requires std::convertible_to<T, int>;
  } || requires {
    requires std::convertible_to<float, T>;
    requires std::convertible_to<T, float>;
};

// note you can put !requires or requires !std::..
template <typename T>
concept NotNumber = !requires {
  requires std::integral<T>;
  requires std::floating_point<T>;
};

// here we ask the compiler to imagine an instance x of template type T
// and then ensure that each statement is valid
// ** Known as functional requires syntax **
template <typename T>
concept Arithmetic = requires(T x){
  x + x;
  x - x;
  x * x;
  x / x;
};

auto testFunction(auto x, auto y){
  return (x + x)/y + (y*x) + (x*y*y);
}

template <typename T>
concept canPerformMyFunction = requires (T x, T y){
  testFunction(x, y);
};

// calling a template implciitly adds the typenames as the parameters
// so you might need to specify the remaining parameters for multiparameter templates
template <typename t1, typename t2>
concept AddableTo = requires (t1 x, t2 y){
  x+y;
};

template<AddableTo<float> t> // sets t2 to a float, t to t1
void Template(t x){
  std::cout << x << " is addable to a float\n";
}

int main(){
  ConstrainedTemplate(4);
  UnConstrainedTemplate(5);
  myFunction(63.2);
  myFunction("Hello world");
  if (IntOrFloatClass<SomeType>){
    std::cout << "The int or float class concept is satisfied\n";
  }
  if (NotNumber<std::string>){
    std::cout << "A string is not a number!\n";
  }
  if (Arithmetic<int>){
    std::cout << "An int satisfied the Arithmetic concept\n";
  }
  if (!Arithmetic<std::string>){
    std::cout << "But a string does not\n";
  }
  if (canPerformMyFunction<float>){
    std::cout << "type float works for the function I defined\n";
  }
  Template(42);

  return 0;
}


