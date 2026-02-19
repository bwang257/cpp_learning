/*
More about auto keyword
- benefits of auto

g++ auto.cpp -o run
*/

#include <iostream>
#include <unordered_map>
#include <utility>

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


int main(){
  type_mismatch();
}

