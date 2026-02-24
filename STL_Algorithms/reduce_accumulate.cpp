/*
Standard library reduce and accumulate algorithms
- designed to simplify large collections of objects into simpler outputs

Compile with:
g++ -std=c++20 reduce_accumulate.cpp -o run
*/

#include <iostream>
#include <vector>
#include <tuple>
#include <cassert>
#include <numeric> // std::reduce and std::accumulate

struct Accumulator {
  int total{};
  int cnt{};

  static Accumulator Add(Accumulator acc, int val){
    return {acc.total + val, acc.cnt +1};
  }

  std::tuple<int, int, float> Log(){
    if (cnt > 0) return {total, cnt, static_cast<float>(total)/ cnt};
    return {total, cnt, 0.f};
  }
};


void stl_reduce(){
  // note that iterators can be view iterators, these algs are not compatible with ranges right now
  // most basic usage: beginning iterator, end iterator --> ends all together
  std::vector<int> myVec{1, 2, 3, 4, 5};
  assert(std::reduce(myVec.begin(), myVec.end()) == 15);

  // can also then take in an initial value and a function/callable that determines
  // how the objects are combined

  // std lib callables include std::multiplies{}, std::plus{}

  // examples
  assert(std::reduce(myVec.begin(), myVec.end(), 2, std::multiplies{}) == 240);
  std::vector Nums{1, -2, 3, -4, 5};

  int Result{std::reduce(Nums.begin()+1, Nums.end(), Nums[0], [](int x, int y){ 
    return std::abs(x) + std::abs(y); 
  })};
  assert(Result == 15);

  // Add later - std::reduce is designed for use in multithreaded environments
  // Note that std::reduce combines the elements in the input in a nondeterministic
  // way so you need to select a deterministc operator



}

void stl_accumulate(){
  // deterministic order of evaluation, left to right
  // also combines using + by default, initial value is not optional though
  std::vector Numbers{1, 2, 3, 4, 5};

  int Result{std::accumulate(Numbers.begin(),Numbers.end(), 1, std::multiplies{})};
  assert(Result == 120);

  // returns type of our initial value
  auto res{std::accumulate(Numbers.begin(), Numbers.end(), 0.5f)};
  assert(res == 15.5f);

  // a more complex example
  std::vector Nums{99, 65, 26, 72, 17};
  auto [total, cnt, avg] = std::accumulate(Nums.begin(), Nums.end(), Accumulator{}, Accumulator::Add).Log();
  assert(total == 279 && cnt == 5 && avg == 55.8f);

  // changing order can be done using reverse iterators or algs in movement_algs.cpp
  auto res2{std::accumulate(Numbers.rbegin(), Numbers.rend(), 0.5f)};
  assert(res2 == 15.5f);
}


int main(){
  stl_reduce();
  stl_accumulate();
  std::cout << "All assertions passed\n";
}


