/*
Counting algorithms in the C++ std library
*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <ranges>

// all algs here can take in a start iterator and sentinel instead of the range
// and a projection function as the last arg


// 1
void count_alg(){
  // std::ranges::count, uses == operator
  std::vector Numbers { 1, 2, 3, 4, 4, 5 };

  // cryptic return type but can implicitly cast to size_t or int64_t
  std::ranges::range_difference_t<std::vector<int>> Fours { std::ranges::count(Numbers, 4) };
  std::cout << "Count of fours: " << Fours << '\n';
}

// 2
void count_if_alg(){
  // std::ranges::count_if
  // counts num elements that satisfy a predicate
  std::vector Numbers { 1, 2, 3, 4, 4, 5 };
  auto isEven{[](int x) { return x % 2 == 0; }};
  auto EvenCount {std::ranges::count_if(Numbers, isEven)};
  std::cout << "Even Count: " << EvenCount << "\n";
}

// 3
void any_of_alg(){
  // std::ranges::any_of
  // stops if element satisfies predicate, returns bool

  // note that predicate can be a member function (ex. &Player::isAlive)
  std::vector Numbers { 1, 2, 3, 4, 4, 5 };
  auto isEven{[](int x) { return x % 2 == 0; } };
  bool IncludesEven { std::ranges::any_of(Numbers, isEven)};

  std::cout << "An even number " << (IncludesEven ? "is" : "is not") << " included\n";
}


// 4
void none_of_alg(){
  // std::ranges::none_of
  // returns true if every predicate call returns false
  // returns true if the range has elements
  std::vector Numbers { 1, 2, 3, 4, 4, 5 };
  auto isEven{ [](int x) { return x % 2 == 0; } };
  bool NoEvenNumbers {std::ranges::none_of(Numbers, isEven)};

  std::cout << "The range contains " << (NoEvenNumbers ? "no" : "some") << " even numbers\n";
}


// 5
void all_of_alg(){
  // std::ranges::all_of
  // opposite of none_of, returns true if every invocation of the predicate returns true
  std::vector Numbers { 1, 2, 3, 4, 4, 5 };
  auto isEven{[](int x) { return x % 2 == 0; }};
  bool AllEvenNumbers { std::ranges::all_of(Numbers, isEven)};

  std::cout << "The range is " << (AllEvenNumbers ? "all" : "NOT all") << " even numbers\n";
}


int main(){
  count_alg();
  count_if_alg();
  any_of_alg();
  none_of_alg();
  all_of_alg();
}



