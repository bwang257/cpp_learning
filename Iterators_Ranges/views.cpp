/*
Discussion of views
- composition, piping, range factories
*/

#include <iostream>
#include <ranges>
#include <vector>

// views allow filtering or processing collections

void Log(int x){
  std::cout << x << ", ";
}

bool FilterEven(int x) {
  return x % 2 == 0;
}

bool FilterOdd(int x) {
  return x % 2 == 1;
}

int main() {
  std::vector Numbers{1, 2, 3, 4, 5};

  // take used for first 3
  std::ranges::for_each(std::views::take(Numbers, 3), Log);
  std::cout << "\n";

  // reverse container
  std::ranges::for_each(std::views::reverse(Numbers), Log);
  std::cout << "\n";

  // views do not own the container, accessing object within the memory address
  // changes to the container
  Numbers.push_back(6);
  Numbers.push_back(7);


  // able to filter based on lambda
  auto FilteredView {std::views::filter(Numbers, [](int i){return i % 2 == 1; })};

  for (const auto& Num : FilteredView) {
    std::cout << Num << ", ";
  }
  std::cout << "\n";

  // because views are ranges, they can be composed - 
  // the output of one view can be the input of another view

  // reverse of first 3 even numbers 
  auto View {std::views::reverse(
    std::views::take(std::views::filter(Numbers, FilterEven), 3)
  )};

  std::ranges::for_each(View, Log);
  std::cout << "\n";

  // pipe operator | to make the composition syntax above more succinct
  // only need to provide 3 for take because the view is provided automatically
  // as an arg. api set up that if no other args needed, no need for ()
  auto View2 {
    std::views::filter(Numbers, FilterOdd) |
    std::views::take(3) |
    std::views::reverse
  };
  std::ranges::for_each(View2, Log);
  std::cout << "\n";

  // zip allows up combine multiple ranges and views together into a single view
  // zipped into tuples, c++23
  // stops at the shortest range

  Numbers.push_back(8); // not shown in zipped view
  std::vector English{
    "Monday", "Tuesday", "Wednesday",
    "Thursday",
    "Friday", "Saturday", "Sunday"};

  std::vector French{
    "Lundi", "Mardi", "Mercredi", "Jeudi",
    "Vendredi", "Samedi", "Dimanche"};

  auto TranslationView{std::views::zip(Numbers, English, French)};

  for (const auto& Tuple : TranslationView) {
    std::cout << std::get<0>(Tuple) << ". "
              << std::get<1>(Tuple) << ": "
              << std::get<2>(Tuple) << '\n';
  }

  // views created without an underlying container - range factories
  // views generated algorithmically

  // ex: iota, can be unbounded std::views::iota(1), but like range(start, end) in python
  for (int x : std::views::iota(1, 11)) {
    std::cout << x << ", ";
  }
  std::cout << "\n";

  // application of unbounded iota view
  std::vector Nums{"One", "Two", "Three"};

  for (const auto& Tuple : std::views::zip(std::views::iota(1), Nums)) {
    std::cout << std::get<0>(Tuple) << ": ";
    std::cout << std::get<1>(Tuple) << '\n';
  }
              
}