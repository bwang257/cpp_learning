/*
Introduction to using concepts to express constraints on classes
*/

#include <concepts>
#include <iostream>
#include <string>

// checking for class members
template <typename T>
concept Sized = requires { T::Size; }; // or requires (T x) {x.Size;};


// checking for class members types
template <typename T>
concept NumberID = requires {
  requires std::integral<decltype(T::id)>;
  // requires std:same_as<int, std::remove_cvref<decltype(T::id)>>;
};


// class methods
// function pointers
void Greet(){
  std::cout << "Hello\n";
}

void Function(int x, std::string y){
  std::cout << "Calling Greet with an int and a string\n";
}
 
template <std::invocable T>
void Call(T function){
  function();
}

// member functions
struct Rock{
  void Render(){ }
};

template <typename T>
// class methods have a hidden argument: pointers to the object it was called on (this ptr)
concept Renderable = std::invocable<decltype(&T::Render), T*>;

template <typename T>
concept specifiedRenderable = requires (T obj, int width, int height) {
  obj.Render(width, height);
};

template <typename T>
concept specifiedRenderable2 = requires (T obj) {
  obj.Render(std::declval<int>(), std::declval<int>());
};

template <std::invocable<int, std::string> T>
void Call(T function){
  function(1, "");
}

// method return types
template <typename t1, typename t2, typename t3>
concept RenderReturns = requires(t1 obj, t2 x){
  { x.Render(x) } -> std::convertible_to<t3>;
  // or -> std::same_as<t3>;
};

// operators
template <typename T1, typename T2>
concept ComparableTo = requires(T1 x, T2 y) {
  { x == y } -> std::convertible_to<bool>;
  { y == x } -> std::convertible_to<bool>; 
};

struct Container {
  Container(int value) : value{value} {};
  int value;
  bool operator==(int y){
    return value == y;
  }
};


int main(){
  Call(&Greet);
  if constexpr (Renderable<Rock>){
    std::cout << "A rock is renderable\n";
  }
  if constexpr (!specifiedRenderable<Rock> && !specifiedRenderable2<Rock>){
    std::cout << "A rock is not renderable with height and width\n";
  }

  // extra parameters of std::invocable are parameters for the function
  if constexpr(std::invocable<decltype(&Function), int, std::string>){
    std::cout << "Function is invocable with a string and an int\n";
  }
  Call(&Function);

  if constexpr(ComparableTo<Container, int>){
    std::cout << "Container is comparable to int\n";
  }
  return 0;
}





