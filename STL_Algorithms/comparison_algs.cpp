/*
8 main comparison stl algorithms in C++

g++ -std=c++23 comparison_algs.cpp -o run
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

struct customType{
  customType(int x) : val{x}{}
  int val{0};
};

void stl_equal(){
  // std::ranges::equal can also be input iterator and sentinel pairs
  std::vector A{1, 2, 3};
  std::vector B{1, 2, 3};
  assert(std::ranges::equal(A,B));

  std::vector<customType> customVec{{1}, {4}, {6}, {7}, {1}};
  std::vector<customType> customVec2{{1}, {4}, {6}, {7}, {1}};
  auto customCompare{[](customType& x, customType& y){ return x.val == y.val; }};
  auto customProject{[](customType& x){ return x.val; }};

  // checking equality with custom comparison or projection function
  assert(std::ranges::equal(customVec, customVec2, customCompare));
  assert(std::ranges::equal(customVec, customVec2, {}, customProject, customProject));

  // compare vectors of different types using projection function
  std::vector<customType> customVec3{{1}, {2}, {3}};
  assert(std::ranges::equal(customVec3, A, {}, customProject, {}));
}

void stl_is_permutation(){
  // std::ranges::is_permutation checks equality without regard for order of elements
  // same inputs as std::ranges::equal
  std::vector A{1, -2, 3, -4};
  std::vector<customType> customVec{{4}, {1}, {2}, {3}};

  assert(std::ranges::is_permutation(A, customVec,
    {}, 
    [](int x){ return std::abs(x); },
    [](customType& x){ return x.val; }
  ));
}

void stl_mismatch(){
  // returns struct with iterators to where mismatch was found 
  std::vector A{1, 2, 3};
  std::vector B{1, 2, 3, 4};
  auto [in1, in2]{std::ranges::mismatch(A, B)};

  // make sure to check if each iterator is at the end
  assert(in1 == A.end());
  assert(in2 != B.end() && *in2 == 4);

  std::vector C{1, 2, 3, 4};
  auto [it1, it2]{std::ranges::mismatch(C, B)};
  // no mismatches found - ranges are equal
  assert(it1 == C.end() && it2 == B.end());

}

void stl_lexicographical_compare(){
  // compares objects until it gets to a mismatch, returns obj1 < obj2
  // not currently available as a range-based algoirithm - have to pass in iterator pair
  std::vector A{1, 2, 3};
  std::vector B{1, 2, 4};

  // returns true if first collection's mismatch obj < second collection's mismatch obj
  assert(std::lexicographical_compare(A.begin(), A.end(), B.begin(), B.end())); 

  std::string a{"apple"};
  std::string b{"banana"};
  assert(std::lexicographical_compare(a.begin(), a.end(), b.begin(), b.end()));

}

void stl_lexicographical_compare_three_way(){
  // also can only accept iterator pairs
  // need to pass result into helper functions that return bool (std::is_lt(), std::is_neq(), etc.)  std::string A{"Apple"};
  std::string A{"Apple"};
  std::string B{"Banana"};

  auto Result{std::lexicographical_compare_three_way(A.begin(), A.end(), B.begin(), B.end())};
  assert(std::is_lt(Result));
  assert(std::is_lteq(Result));
  assert(std::is_neq(Result));

  // note that std::string should generally just be compared with <, ==, >
}

// c++23
void stl_starts_with(){
  // checks if first range passes equality with obj in second range
   std::vector A{1, 2, 3, 4, 5};
  std::vector B{1, 2, 3};

  assert(std::ranges::starts_with(A,B)); // can also had projection + predicate functions like equal/permutation

  // C++20 std::string has start_with as a member function
  std::string fullName{"Brian Wang"};
  std::string firstName{"Brian"};
  assert(fullName.starts_with(firstName));
}

// c++23
void stl_ends_with(){
  // essentially opposite of starts with

  std::vector A{1, 2, 3, 4, 5};
  std::vector B      {3, 4, 5};
  assert(std::ranges::ends_with(A,B));

  // C++20 std::string has this as a member function
  std::string fullName{"Brian Wang"};
  std::string lastName{"Wang"};
  assert(fullName.ends_with(lastName));
}

int main(){
  stl_equal();
  stl_is_permutation();
  stl_mismatch();
  stl_lexicographical_compare();
  stl_lexicographical_compare_three_way();
  stl_starts_with();
  stl_ends_with();

  std::cout << "All assertions passed\n";
}