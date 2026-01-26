/*
Minimum and maximum algorithms in the C++ std library
*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <ranges> 

// if <C++20, can exclude ranges specification (std::ranges::min --> std::min)
// but projection function and flexible sentinel pattern not allowed


// note like most algorithms, args you can add to these std lib algs 
// are the custom comparison callable and a projection function

// to support min max algorithms, we generally need to implement all 6 comparison operators

struct MyStruct {
  int Value;
  bool operator<(const MyStruct& Other) const {
    return Value < Other.Value;
  }
  bool operator<=(const MyStruct& Other) const {
    return Value <= Other.Value;
  }
  bool operator>(const MyStruct& Other) const {
    return Value > Other.Value;
  }
  bool operator>=(const MyStruct& Other) const {
    return Value >= Other.Value;
  }
  bool operator==(const MyStruct& Other) const {
    return Value == Other.Value;
  }
  bool operator!=(const MyStruct& Other) const {
    return Value != Other.Value;
  }
};


int main() {
  
  // clamp(val, min, max)
  // returns min if val < min, max if val > max, else val
  using std::ranges::clamp;
  std::cout
    << "Clamp -30: " << clamp(-30, 0, 255)
    << "\nClamp 100: " << clamp(100, 0, 255)
    << "\nClamp 300: " << clamp(300, 0, 255) << "\n";

  
  std::vector Numbers{2, 3, 1, 4, 5};

  // min/max
  // two vals or range/subrange, not iterator-sentinel pair
  // returns reference to smallest/largest object
  std::cout << "The min between 4 and 7 is " << std::ranges::min(4, 7) << "\n"; 
  std::cout << "The max between 4 and 7 is " << std::ranges::max(4, 7) << "\n"; 
  int Result{std::ranges::min(std::ranges::subrange(Numbers.begin() + 1, Numbers.end() - 1))};
  int Result3{std::ranges::max(std::ranges::subrange(Numbers.begin() + 1, Numbers.end() - 1))};
  std::cout << "Smallest number: " << Result << "\n";
  std::cout << "Largest number: " << Result3 << "\n";

  // min_element / max_element
  // returns iterator to smallest object
  // supports iterator-sentinel pairs
  auto Result2{std::ranges::min_element(Numbers)};  
  auto Result4{std::ranges::max_element(Numbers)};  
  std::cout << "The min element is at index: " << std::distance(Numbers.begin(), Result2);
  std::cout << "\nIts value is: " << *Result2 << "\n";
  std::cout << "The max element is at index: " << std::distance(Numbers.begin(), Result4);
  std::cout << "\nIts value is: " << *Result4 << "\n";

  // minmax
  // returns struct with min and max members
  // if multiple max objects, will contain the last/rightmost one in the range
  // no support for iterator-sentinel pair but can use subrange
  auto [min, max]{std::ranges::minmax(10, 1)};  
  std::cout << "Min: " << min << ", Max: " << max << "\n";

  const auto& Result5 { std::ranges::minmax(Numbers) };
  std::cout << "Smallest: " << Result5.min;
  std::cout << "\nLargest: " << Result5.max << "\n";

  // minmax_element
  // returns iterator struct
  // supports iterator/sentinel pair
  auto [min_it, max_it] { std::ranges::minmax_element(Numbers)};

  std::cout << "Min element: " << *min_it << ", Index: " << std::distance(Numbers.begin(), min_it);
  std::cout << "\nMax element: " << *max_it << ", Index: " << std::distance(Numbers.begin(), max_it) << "\n";
}



