/*
Discussion of 5 common STL Partition Algorithms 

Compile with:
g++ -std=c++20 partition_algs.cpp -o run
*/

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// partitioning more efficient than sorting if all we are doing is grouping
// terms together

// use universal reference
void print_range(std::ranges::range auto&& range){
  for (const auto& val : range){
    std::cout << val << ", ";
  }
  std::cout << "\n";
}

void stl_partition(){
  // std::ranges::partition
  // returns subrange to second group of partitioned range

  std::vector nums{2, -5, 4, -7, 8, 9, -22, 17};
  auto my_predicate{[](int x){ return std::abs(x) % 2 == 1; }};

  std::cout << "Original: ";
  print_range(nums);

  auto second_subr{std::ranges::partition(nums, my_predicate)};

  std::cout << "Partitioned (by odd): ";
  print_range(nums);

  // can use second_subr to find first_subrange
  std::ranges::subrange first_subr{nums.begin(), second_subr.begin()};

  std::cout << "First subrange: ";
  print_range(first_subr);
  std::cout << "Returned second subrange: ";
  print_range(second_subr);

  std::cout << "\n";
}


void stl_stable_partition(){
  // std::ranges::stable_partition
  // same API as parition but makes sure that relative
  // order of elements preserved

  std::vector nums{2, -5, 4, -7, 8, 9, -22, 17};
  auto my_predicate{[](int x){ return std::abs(x) % 2 == 1; }};

  std::cout << "Original: ";
  print_range(nums);

  auto second_subr{std::ranges::stable_partition(nums, my_predicate)};

  std::cout << "Partitioned (by odd): ";
  print_range(nums);

  // can use second_subr to find first_subrange
  std::ranges::subrange first_subr{nums.begin(), second_subr.begin()};

  std::cout << "First subrange: ";
  print_range(first_subr);
  std::cout << "Returned second subrange: ";
  print_range(second_subr);

  std::cout << "\n";
}



void stl_partition_copy(){
  // std::ranges::parition_copy
  // leaves original container unmodified, copies elements
  // into two other ranges 

  std::vector A{1, -6, 4, 2, 5, 7};
  std::vector<int> Even;
  std::vector<int> Odd;

  // make sure output has enough space, usually don't know
  // so we have to oversize
  Even.resize(A.size());
  Odd.resize(A.size());

  auto isEven{[](int x){ return x % 2 == 0; }};

  // returns partition_copy_result, contains in (input sentinel), and o1, o2 iterators to one past last element
  // in the two output ranges
  auto [in, o1, o2]{ std::ranges::partition_copy(A, Even.begin(), Odd.begin(), isEven)};

  std::cout << "Even Partition Size: " << o1 - Even.begin() << "\n";
  std::cout << "Odd Partition Size: " << o2 - Odd.begin() << "\n";

  // Erasing excess elements from the output
  Even.resize(o1 - Even.begin());
  Odd.resize(o2 - Odd.begin());

  std::cout << "Even: ";
  print_range(Even);
  std::cout << "Odd: ";
  print_range(Odd);

  std::cout << "\n";
}


void stl_is_partitioned(){
  // std::ranges::is_partitioned
  // check if a range is partitioned according to a predicate func

  std::vector A{2, -6, 4, 1, -5, 3};
  auto isEven{[](int x){ return x % 2 == 0; }};
  auto isNeg{[](int x){ return x < 0; }};

  if (std::ranges::is_partitioned(A, isEven)) {
    std::cout << "A is partitioned with respect to isEven\n";
  }

  if (!std::ranges::is_partitioned(A, isNeg)) {
    std::cout << "A is NOT partitioned with respect to isNeg\n";
  }
  std::cout << "\n";
}

void stl_partition_point(){
  // std::ranges::partition_point
  // returns iterator to first element where predicate func returns false

  std::vector A{2, -6, 2, 3, 0, 8};
  auto isEven{[](int x){ return x % 2 == 0; }};
  auto PartitionPoint{std::ranges::partition_point(A, isEven)};

  if (PartitionPoint == A.end()) {
    std::cout << "The second partition is empty - All elements returned true\n";
  } else {
    std::cout << "First element that returned false was " << *PartitionPoint << "\n";
  }

  std::cout << "\n";
}

// custom types
// partition algorithm involves move assignment to avoid excessive copying
// may need to define custom move assignment and swap functions



int main(){
  stl_partition();
  stl_stable_partition();
  stl_partition_copy();
  stl_is_partitioned();
  stl_partition_point();
}