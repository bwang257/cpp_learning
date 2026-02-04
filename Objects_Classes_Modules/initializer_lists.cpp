/*
Creating objects using lists

g++ -std=c++20 initializer_lists.cpp -o run
*/

#include <iostream>
#include <format>
#include <vector>

struct TripleVal {
  int x{0};
  int y{0};
  int z{0};

  void logVals(){
    std::cout << std::format("TripleVal values: x: {}, y: {}, z: {}\n", x, y, z);
  }
};

// list initialization with functions
TripleVal get_struct(){
  return {7, 8, 9};
}

// reverse
void log_struct(TripleVal st){
  st.logVals();
}

// apply std::initializer_list<T> to custom container
// std::initializer_list<T> is a lightweight, read only wrapper
// thus, fast to copy and generally passed by value
// it is a homogenous container
template <typename T>
class CustomContainer {
public:
  CustomContainer(
    std::initializer_list<T> Contents) : Container{Contents} {}

  auto begin() const{ return Container.begin(); }
  auto end() const{ return Container.end(); }

private:
  std::vector<T> Container;
};



int main(){

  // this actually known as aggregate initialization
  // only applied when no user-defined constructors, non-public var (unless inherited)
  // no virtual functions, no private/protected/virtual base classes

  TripleVal x{1, 2, 3}; 
  x.logVals();


  x = {4, 5, 6}; // list initialization during assignment
  x.logVals();

  x = get_struct();
  x.logVals();

  log_struct({10, 11, 12});

  CustomContainer nums{13, 14, 15, 16, 17};
  for (const auto& x : nums){
    std::cout << x << ", ";
  }
  std::cout << "\n";

  // Designated Initialization (C++20)
  TripleVal y{.x = 55, .z = 67}; // allows us to omit
  y.logVals();
}



