/*
Discussion of STL Algorithms for removing objects from containers
- every std alg here can accept a projection function as another arg
- can also use a iterator-sentinel pair instead of a range
- if we don't use ranges namespace, we must use iterator-iterator pair with no projection functions
  - plus remove and remove_if return iterator instead of subrange, slightly less friendly
*/

#include <iostream>
#include <algorithm>
#include <ranges>
#include <vector>
#include <string>


void stl_remove(){
  // std::ranges::remove
  // takes in range and element to remove
  // uses == operator
  // does not modify container size, relevant elements are at front, potential surplus of elements at the end
  // returns subrange of this surplus

  // pattern of moving elements we want t keep to the left of a container and then truncating it is 
  // called the remove-eras idiom. Just call the container's erase function afterwards with surplus begin/end iterators as args

  std::vector Source{1, 2, 3, 4, 5, 6};
  std::cout << "Inital range: ";
  for (int i{}; i < Source.size();){
    std::cout << Source[i++] << ", ";
  }
  std::cout << "\n";
  auto Surplus{std::ranges::remove(Source, 3)}; // can also structured binding here to access the begin/end iterators of surplus


  std::cout << "Objects in Source: ";
  for (auto Num : Source) {
    std::cout << Num << ", ";
  }
  std::cout << "\nSurplus: ";
  for (auto Num : Surplus) {
    std::cout << Num << ", ";
  }
  std::cout << "\n";
}

void stl_remove_if(){
  // std::ranges::remove_if
  // takes in predicate function
  // returns subrange with objects to erase
  std::vector Source{1, 2, 3, 4, 5, 6};
  auto isEven{[](int x) { return x % 2 == 0; }};

  auto Result{std::ranges::remove_if(Source, isEven)};

  std::cout << "Objects in Source: ";
  for (auto Num : Source) {
    std::cout << Num << ", ";
  }

  std::cout << "\nObjects to Erase:  ";
  for (auto Num : Result) {
    std::cout << Num << ", ";
  }
  std::cout << "\n";
}

void stl_remove_copy(){
  // std::ranges::remove_copy
  // copies obj from one loc to another, but doesn't copy objects == to a specified obj
  // returns in (input range sentinel) and out (iterator beyond last element copied in output range)
  std::vector Source{1, 2, 3, 4, 5, 6};
  std::vector Destination{0, 0, 0, 0, 0, 0};

  auto [in, out]{std::ranges::remove_copy(Source, Destination.begin(), 3)};

  std::cout << "The source had " << std::distance(Source.begin(), in) << " elements.\n";

  std::cout << std::distance( Destination.begin(), out) << " elements were copied.";

  Destination.erase(out, Destination.end());

  std::cout << "\nObjects in Destination: ";
  for (auto Num : Destination) {
    std::cout << Num << ", ";
  }
  std::cout << "\n";
}

void stl_remove_copy_if(){
  // std::ranges::remove_copy_if
  // same thing as std::ranges::remove_copy but takes in predicate func
   std::vector Source{-3, -2, -1, 0, 1, 2, 3};
  std::vector Destination{0, 0, 0, 0, 0, 0, 0};

  auto Predicate{[](int x) { return x >= 2; }};

  auto [in, out]{std::ranges::remove_copy_if(Source, Destination.begin(), Predicate)};

  std::cout << "The source had " << std::distance(Source.begin(), in) << " elements.\n";

  std::cout << std::distance(Destination.begin(), out) << " elements were copied.";

  Destination.erase(out, Destination.end());

  std::cout << "\nObjects in Destination: ";
  for (auto Num : Destination) {
    std::cout << Num << ", ";
  }
  std::cout << "\n";
}

// void stl_remove(){

// }


int main(){
  stl_remove();
  stl_remove_if();
  stl_remove_copy();
  stl_remove_copy_if();
}


