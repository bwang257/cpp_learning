/*
5 Main STL set algorithms
- customer comparers for differently sorted sets or custom types
- note that, while not sure, you can add two projector functions for 
  each of the sets: ex. std::ranges::includes(A, B, {}, Projector, Projector)
- if we remove ranges namespace, you have to pass iterator pair, no projection supported

Compile with:
g++ -std=c++20 stl_set_algs.cpp -o run
*/

// note: "set" here applies to any type of container with forward iterators
// the stl algorithms require inputs to be sorted

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

void print_range(std::ranges::range auto&&);

void subsets(){
  // let A,B be two sets. B ⊆ A if A (superset) includes B (subset)
  std::set A{1, 2, 3};
  std::set B{1, 2};

  if (std::ranges::includes(A, B)) {
    std::cout << "A ⊇ B\n";
  }

  // default assumption is that our sets are sorted in ascending
  auto Comparer{[](const int& A, const int& B){ return A > B; }}; // could also use std::ranges::greater() stl functor

  std::set C{3, 2, 1};
  if (std::ranges::includes(C, B, Comparer)){
    std::cout << "C ⊇ B\n";
  }


  std::cout << '\n';
}

void unions(){
  // std::merge can contain dupliciates
  // using vector here
  std::vector A{1, 2, 3};
  std::vector B{3, 4, 5};

  std::cout << "Set A: ";
  print_range(A);
  std::cout << "Set B: ";
  print_range(B);

  std::vector<int> Results;
  Results.resize(A.size() + B.size()); // make sure enough memory

  // structured binding here
  auto [AEnd, BEnd, UnionEnd] = std::ranges::set_union(A, B, Results.begin()); // two sets + iterator for where the union is to be created
  std::cout << "Union Size: " << UnionEnd - Results.begin() << '\n';
  std::cout << "Union: ";
  Results.erase(UnionEnd, Results.end());
  print_range(Results);
  std::cout << "\n";
}

void intersections(){
  // same return type as std::ranges::set_union
  std::vector A{1, 2, 3};
  std::vector B{2, 3, 4};
  std::cout << "Set A: ";
  print_range(A);
  std::cout << "Set B: ";
  print_range(B);

  std::vector<int> Results;
  Results.resize(std::min(A.size(), B.size()));

  auto [AEnd, BEnd, IntersectionEnd]{std::ranges::set_intersection(A, B, Results.begin())};

  std::cout << "Intersection Size: " << IntersectionEnd - Results.begin()<< '\n';

  Results.erase(IntersectionEnd, Results.end());
  std::cout << "Intersection: ";
  print_range(Results);
  std::cout << "\n";
}

void differences(){
  // returns iterator to end of first range and last element of output
  std::vector A{1, 2, 3};
  std::vector B{3, 4, 5};
  std::cout << "Set A: ";
  print_range(A);
  std::cout << "Set B: ";
  print_range(B);

  std::vector<int> Results;
  Results.resize(A.size());

  auto [AEnd, DifferenceEnd]{std::ranges::set_difference(A, B, Results.begin())};

  std::cout << "Difference Size: " << DifferenceEnd - Results.begin() << '\n';

  Results.erase(DifferenceEnd, Results.end());
  std::cout << "Difference: ";
  print_range(Results);

  std::cout << "\n";
}

void symmetric_difference(){
  // items in either set or not both (exclusive or - xor)
  // return type same as unions and intersections
  // {1,2,3} △ {2,3,4} = {1,4}
  std::vector A{1, 2, 3};
  std::vector B{2, 3, 4};
  std::cout << "Set A: ";
  print_range(A);
  std::cout << "Set B: ";
  print_range(B);

  std::vector<int> Results;
  Results.resize(A.size() + B.size());

  auto [AEnd, BEnd, SymmetricDifferenceEnd]{std::ranges::set_symmetric_difference(A, B, Results.begin())};

  std::cout << "Symmetric Difference Size: " << SymmetricDifferenceEnd - Results.begin() << '\n';

  Results.erase(SymmetricDifferenceEnd, Results.end());
  
  std::cout << "Symmetric Difference: ";
  print_range(Results);

  std::cout << "\n";
}

int main(){
  subsets();
  unions();
  intersections();
  differences();
  symmetric_difference();
}

// helper func for printing ranges
void print_range(std::ranges::range auto&& range){
  for (const auto& val : range){
    std::cout << val << ", ";
  }
  std::cout << "\n";
}