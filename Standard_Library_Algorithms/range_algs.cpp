/*
Explores of 8 commonly used standard library algorithms (applied to ranges)
*/

#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cmath>
#include <random>
#include <numeric>


void Log(int Number){
  std::cout << Number << ", ";
}


// 1
void for_each_algorithm(){
  // std::ranges::for_each()
  // accepts range as first arg, function as second, projection function third
  // while not shown here, the range can be a view or an interator-sentinel pair, 
  // can contain a initialized subrange piped into std::views::reverse, etc.

  std::vector Numbers{1, 2, 3, 4, 5};
  std::cout << "for_each: ";
  std::ranges::for_each(Numbers, [](int& x){ std::cout << x << ", ";});
  std::cout << "\n";
  std::cout << "applying projection function: ";
  std::ranges::for_each(Numbers, [](int x){ std::cout << x << ", ";}, [](int x){ return x*2; });
  std::cout << "\n";
  std::cout << "original vector not changed: ";
  std::ranges::for_each(Numbers, [](int& x){ std::cout << x << ", ";});
  std::cout << "\n";
}

// 2
void transform_algorithm(){
  // std::ranges::transform
  // populates a rnage by passsing values from some other range into a function
  // return values used to populate the target range
  // returns a struct std:ranges::in_out_result that has two vals
    // in: iterator pointing to where the input range ended
    // out: iterator to the last element inserted into the output
    // can be accessed through strcutrued binding
  
  // if take in two ranges, returns struct with in1, in2, and out. 

  std::vector Input{1, 2, 3, 4, 5};
  std::vector<int> Output;
  Output.resize(8);

  auto [in, out] = std::ranges::transform(Input, Output.begin(), [](int x){ return x * 2; });
  std::cout << "Output: ";
  std::ranges::for_each(Output, Log);
  std::cout << "\nObjects Transformed: " << std::distance(Output.begin(), out);
  std::cout << "\nLast Object: " << *(out - 1);

  Output.erase(out, Output.end());
  std::cout << "\nTrimmed Output: ";
  std::ranges::for_each(Output, Log);
  std::cout << "\n";

  // binary transform
  std::vector Input1{1, 2, 3, 4, 5};
  std::vector Input2{2, 3, 4, 5, 6};
  std::vector<int> Output2;
  Output2.resize(Input1.size());

  // note functional templated functors
  // std::ranges::transform(Input1, Input2, Output.begin(), [](int x, int y){ return x + y; });
  std::cout << "Sum of input1 and input2: ";
  std::ranges::transform(Input1, Input2, Output2.begin(), std::plus{});
  std::ranges::for_each(Output2, Log);
  std::cout << "\n";
}

// 3
void equal_algorithm(){
  // std::ranges::equal
  // returns true if the values of two ranges are equal and in the same order
  // but can customize functionality
  std::vector input1{2, 1, 3};
  std::vector input2{1, 2, 3};
  if (!std::ranges::equal(input1, input2)){
    std::cout << "the ranges are not initially equal\n";
  }

  auto within1{
    [](int x, int y){
      return std::abs(x-y) <= 1;
    }
  };
  if (std::ranges::equal(input1, input2, within1)){
    std::cout << "the ranges are within 1 of eachother\n";
  }

  // can take in input1, input2, default comparison function, and then two projection functions
  std::vector Input1{1, 2, 3};
  std::vector Input2{-1, -2, -3};

  auto Abs{[](int x){ return std::abs(x); }};

  if (std::ranges::equal(Input1, Input2, {}, {}, Abs)) {
    std::cout << "Absolute value of second range equal to first range\n";
  }

  // variation of equals is the permutaitons algorithm that just checks if same values, regardless of order
  std::vector Input3{3, 2, 1};
  if (std::ranges::is_permutation(Input1, Input3) && !std::ranges::equal(Input1, Input3)){
    std::cout << "Input1 and Input3 contain the same elements, just in different orders\n";
  }
}

// 4
void fill_algorithm(){
  // std::ranges::fill
  // takes in a range and a object, fills the range with copies of that object
  std::vector<int> Numbers;
  Numbers.resize(5);
  std::cout << "Initial state: ";
  std::ranges::for_each(Numbers, Log);
  std::cout << "\n";
  std::cout << "After Filling: ";
  std::ranges::fill(Numbers, 10);
  std::ranges::for_each(Numbers, Log);
  std::cout << "\n";
}

// create a generator
struct NumberGenerator { 
  int n{1};
  int operator()(){
    return std::pow(n++, 2);
  }
};

// create rng
struct RandomNumberGenerator{
  public: 
    int operator()(){return Dist(Engine); }
  private:
    static inline std::uniform_int_distribution Dist{1, 10};
    static inline std::random_device Device;
    static inline std::mt19937 Engine{Device()};
};

// 5
void generate_algorithm(){
  // std::ranges::generate
  // populates a range by calling a function for each positon in the range
  NumberGenerator generator;
  std::array<int, 7> nums;
  std::ranges::generate(nums, generator);

  for (const int& num : nums){
    std::cout << num << ", ";
  }
  std::cout << '\n';

  // apply <random>
  RandomNumberGenerator RNG;
  std::array<int, 7> Numbers;
  std::ranges::generate(Numbers, RNG);

  for (const int& num : Numbers){
    std::cout << num << ", ";
  }
  std::cout << '\n';
}

// 6
void iota_algorithm(){
  // std::iota
  // 3 args: iterator to start and end, what first number should be
  // generates sequence of incrementing integers
  // note use of std::views::iota in views
  std::array<int, 10> Numbers;
  Numbers[0] = 43;
  std::iota(Numbers.begin()+1, Numbers.end(), 82);
  std::ranges::for_each(Numbers, Log);
  std::cout << "\n";
}

// 7
void merge_algorithm(){
  // std::ranges::merge
  // takes in two SORTED ranges and the iterator to output location
  // can take in optional comparison function
  
  // ranges must be sorted in the same way the final range should be
  std::vector Numbers1{5, 3, 1};
  std::vector Numbers2{4, 3, 2};
  if (std::ranges::is_sorted(Numbers1, std::greater{}) && std::ranges::is_sorted(Numbers2, std::greater{})){
    std::cout << "Inputs are sorted in descending order!\n";
  }

  std::vector<int> Output;
  Output.resize(Numbers1.size() + Numbers2.size());

  auto Descending{ [](int a, int b){ return a > b; }};

  // note descending can be replaced with std::greater{}
  std::ranges::merge(Numbers1, Numbers2, Output.begin(), Descending);

  std::ranges::for_each(Output, Log);
  std::cout << "\n";

  // merge includes duplicates. std::ranges::set_union does not
  std::vector A{1, 3, 5};
  std::vector B{1, 2, 3, 4};

  // Merge
  std::vector<int> Merged;
  Merged.resize(A.size() + B.size());
  std::ranges::merge(A, B, Merged.begin());
  std::cout << "Merge Result: ";
  std::ranges::for_each(Merged, Log);

  // Union
  std::vector<int> Union;
  Union.resize(A.size() + B.size());
  auto [in1, int2, out] =
    std::ranges::set_union(A, B, Union.begin());
  Union.erase(out, Union.end());
  std::cout << "\nUnion Result: ";
  std::ranges::for_each(Union, Log);
  std::cout << "\n";

}

// 8
void sample_algorithm(){
  // std::ranges::sample
  // copies a random sample of objects from one range into another
  // does this without replacement
  std::vector Numbers{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  std::vector<int> Output;
  Output.resize(5);

  auto RNG{ std::mt19937{std::random_device{}()}};
  std::ranges::sample(Numbers, Output.begin(), Output.size(), RNG);

  // output is in releative order they were input
  std::cout << "before shuffling: ";
  std::ranges::for_each(Output, Log);
  std::cout << "\n";

  std::cout << "after shuffling: ";
  std::ranges::shuffle(Output, RNG);
  std::ranges::for_each(Output, Log);
  std::cout << "\n";
}

int main(){
  for_each_algorithm();
  std::cout << "\n";

  transform_algorithm();
  std::cout << "\n";

  equal_algorithm();
  std::cout << "\n";

  fill_algorithm();
  std::cout << "\n";

  generate_algorithm();
  std::cout << "\n";

  iota_algorithm();
  std::cout << "\n";

  merge_algorithm();
  std::cout << "\n";

  sample_algorithm();
}
