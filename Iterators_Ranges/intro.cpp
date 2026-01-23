


// range introduced c++20, any type that has a begin and end method
// range based for loop syntax: ex. for (int x: Vector) ...
// or to not copy them: for (const int& x: Vector) ...


// just like with iterators, there are corresponding range types
// forward/bidirectional/random-access ranges

#include "intro.hpp"
#include <iostream>
#include <list>
#include <forward_list>
#include <vector>
#include <ranges> // uses c++20 concepts

// application of range concepts
template <typename T>
void Log(T Range) {
  if constexpr (std::ranges::forward_range<T>) {
    std::cout << " - Forward Range\n";
  }
  if constexpr (
    std::ranges::bidirectional_range<T>
  ) {
    std::cout << " - Bidirectional Range\n";
  }
  if constexpr (
    std::ranges::random_access_range<T>
  ) {
    std::cout << " - Random Access Range\n";
  }
}

// can only accept bidirectional ranges
void LogLast(std::ranges::bidirectional_range auto R){
  std::cout << *(std::next(R.end(), -1));
}

int main(){
  std::cout << "std::forward_list<int>:\n";
  Log(std::forward_list{1, 2, 3});

  std::cout << "\nstd::list<int>:\n";
  Log(std::list{1, 2, 3});

  std::cout << "\nstd::vector<int>:\n";
  Log(std::vector{1, 2, 3});

  Party<Person> myparty;
  Person a{"Brian"};
  myparty.add_member(a);
  myparty.add_member(Person{"Andrew"}); // constructs prvalue, then actually is forwarded as a r-value
  myparty.add_member("Ben");

  // check assertions given implementations of begin and end
  static_assert(std::ranges::random_access_range<Party<Person>>);
  static_assert(std::ranges::contiguous_range<Party<Person>>);

  // range based loop
  std::cout << "Members in myparty: ";
  for (const Person& member : myparty){
    std::cout << member.name << ", ";
  }
  std::cout << "\n";

}