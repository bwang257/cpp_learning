/*
More about auto keyword
- benefits of auto
- when not to use auto

g++ auto.cpp -o run
*/

#include <iostream>
#include <unordered_map>
#include <vector>
#include <utility>
#include <cassert>

#define NumVals 5

int copy_times;

struct myObj{
  myObj(int x): x{x}{}

  // def copy constructor
  myObj(const myObj& other): x{other.x}{
    ++copy_times;
  }
  int x;
};

// benefits of auto against type mismatches in explicit type declarations
void type_mismatch(){
  std::unordered_map<int, myObj> myObjs;
  for (int i{}; i < NumVals; ++i){
    myObjs.emplace(i, i);
    // myObjs.insert({i, myObj{i}}); this would create copies on myObj{i}
    // myObjs[i] = myObj{i}; // this would actually default construct myObj first
  }

  // the keys of a map are const, but you can miss that
  for (const std::pair<int, myObj>& p: myObjs){
    //
  }

  std::cout << "myObj was copied " << copy_times << " times\n";

  copy_times = 0; // reset

  // auto resolves that issue
  for (const auto& p: myObjs){
    //
  }

  std::cout << "myObj was copied " << copy_times << " times\n";
}

// we have some helper that returns a vector of bools
std::vector<bool> check_val(const myObj& obj){
  assert(obj.x % 2 == 0);
  return {true, false, true, true};
}

// use of auto can lead to undefined behavior with proxy classes
void proxy_classes(){
  myObj x{2};
  
  // [] for a bool vector returns std::vector<bool>::reference
  // rather than bool& because C++ forbids references to bits
  // the returned vector is destroyed at the end of the vehavior
  auto result = check_val(x)[1];
  if (std::is_same<decltype(result), std::vector<bool>::reference>::value){};

  // should use the explicitly typed initializer idiom:
  auto result2 = static_cast<bool>(check_val(x)[1]);
  if (!result2) std::cout << "Using explicitly typed initializer idiom\n";
}

int main(){
  type_mismatch();
  proxy_classes();
}

