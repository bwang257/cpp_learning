/*
Discusses standard library movement algorithms
*/

#include <algorithm>
#include <iostream>
#include <vector>

int main() {

  // std::ranges::move
  // moves objects from a source range to a destination range
  // returns struct with in (setinel for source range) and out
  // ptr to position after last element moved 

  std::vector Source{1, 2, 3};
  std::vector Destination{0, 0, 0, 0, 0};
  auto [in, out]{std::ranges::move(Source, Destination.begin() + 1)};

  std::cout << "Values in Destination:\n";
  for (auto& Num : Destination) {
    std::cout << Num << ", ";
  }
  std::cout << "\n";
  std::cout << "The input had " << std::distance(Source.begin(), in) << " objects\n";

  std::cout << "The output iterator is at index " << std::distance(Destination.begin(), out) << "\n";

}