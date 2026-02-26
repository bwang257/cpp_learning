/*
C++23 Fold Algorithms
- My Mac was not able to run some of these assertions
- compiler did not recognize _first and fold right stl algs

Compile with: 
g++ -std=c++23 fold_algs.cpp -o run?
*/

// similar to reduce and accumulate algs, take collection of objs
// and return singular result. Range based and more control

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

void stl_fold_left(){
  // very similar to std::accumulate
  // type returned is same as initial val, can use custom operators too
  
  std::vector Numbers{-1, 2, -3, 4, 5};
  assert(std::ranges::fold_left(Numbers, 0, std::plus{}) == 7);
  assert(std::ranges::fold_left(Numbers, 0.f, [](int x, int y){return std::abs(x) + std::abs(y);}) == 15.f);
}

template<typename T>
struct ZeroSentinel {
  bool operator==(T iter) const{
    return iter == ContainerEnd || *iter == 0;
  }

  T ContainerEnd;
};

void stl_fold_left_iter(){
  // use when sentinel is not trivial
  // returns where the sentinel is triggers + resulting value
  
  std::vector Numbers{1, 3, 5, 0, 10};
  auto [Iter, Result]{ std::ranges::fold_left_with_iter(Numbers.begin(), 
                       ZeroSentinel{Numbers.end()}, 1, std::multiplies{})};
  
  assert(Iter != Numbers.end()); // range had a zero
  assert(*(Iter-1) == 5); // number before sentinel
  assert(Result == 15);
}

// void stl_fold_left_first(){
//   // takes in no initial value, uses first element as first element
//   // returns optional to handle edge case where the range is empty
//   std::vector Numbers{1, 2, 3, 4, 5};
//   std::optional Result{std::ranges::fold_left_first(Numbers, std::plus{})};
//   assert(Result.has_value());
//   assert(Result.value() == 15);
// }

// void stl_fold_left_first_with_iter(){
//   // combines first and iter left folds
//   // returns val as an optional
//   std::vector Numbers{0, 3, 5, 0, 10};

//   auto [Iter, Result]{std::ranges::fold_left_first_with_iter(Numbers.begin(),
//       ZeroSentinel{Numbers.end()},
//       std::multiplies{})};

//   assert(!Result.has_value());
//   assert(Iter != Numbers.end());
// }

// void stl_fold_right(){
//   // starts with last elements, requires a bidirectional range
//    std::vector Numbers{1, 2, 3};

//   int LeftResult{std::ranges::fold_left(Numbers, 0, std::minus{})};
//   assert(LeftResult == -6);
//   int RightResult{std::ranges::fold_right(Numbers, 0,std::minus{})};
//   assert(LeftResult != RightResult);

//   // Note how the operator is being applied, it uses right most operand
//   Numbers.resize(1);
//   int LeftResult2{std::ranges::fold_left(Numbers, 10, std::minus{})}; // 1-10
//   assert(LeftResult2 == -9);
//   int RightResult2{std::ranges::fold_right(Numbers, 10, std::minus{})};
//   assert(RightResult2 == 9);
// }

// fold_right_last sets the last value as the initial value and returns an optional
// but like fold_right, my compiler does not seem to recognize it

int main(){
  stl_fold_left();
  stl_fold_left_iter();
  // stl_fold_left_first();
  // stl_fold_left_first_with_iter();
  // stl_fold_right();

  std::cout << "All assertions passed.\n";
}