/*
Introduction to the 8 main searching algorithms in the C++ stdlib
*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <cassert>
#include <functional>

struct CustomType{
  int value;
  auto operator<=>(const CustomType&) const = default;
  bool operator==(const CustomType&) const = default;
};


// Binary Search O(n) or (log n)
void binary_search_algorithm(){
  // std::ranges::binary_search
  // benefits from random access range and iterator but does not require it. 
  // requires sorted range (or more technically partitioned with respect to the object we are searching for)
  // C++ binary search can be O(log n) and O(n)
  // returns bool whether obj was found

  // note need to provide override <=> for bin search to work on custom types
  // or pass func as third parameter

  // 4th param can be projection function
  std::vector Numbers{1, 4, 7, 8, 9, 20, 100};
  bool result{std::ranges::binary_search(Numbers, 20)};
  if (result){ std::cout << "20 was found in the vector!\n"; }

  // lower_bound either returns an iterator to the element of an iterator to where
  // the element would be. could be end
  // allows actually accessing the object
  auto it{std::ranges::lower_bound(Numbers, 20)};
  assert(it == Numbers.begin()+5);
  
  auto it2{std::ranges::lower_bound(Numbers, 15)};
  std::cout << "Lower bound says that 15 should go in position " << std::distance(Numbers.begin(), it2) << "\n";

  auto it3{std::ranges::lower_bound(Numbers, 101)};
  if (it3 == Numbers.end()){
    std::cout << "Lower bound says that 101 should go at the end of the vector\n";
  }
  // can then insert, allows for insertion while perserving sorted order
  Numbers.insert(it3, 101);

  std::vector vec{CustomType{1}, CustomType{2}, CustomType{4}, CustomType{5}, CustomType{6}};
  CustomType targ{5};
  auto Result{std::ranges::lower_bound(vec, targ)};
  if (Result != vec.end()){ std::cout << "Customer type with val 5 found in the vector\n"; }


  // upper_bound method returns highest possible index 
  // ex. upper == lower + 1 if searching for 4 in 1, 2, 3, 4, 5
  // upper == lower if 1, 2, 3, 5

  std::vector newnums{1, 2, 3, 4, 4, 4, 5};

  auto Lower{std::ranges::lower_bound(newnums, 4)};
  std::cout << "Lower Bound Index " << std::distance(newnums.begin(), Lower);
  auto Upper{std::ranges::upper_bound(newnums, 4)};
  std::cout << "\nUpper Bound Index " << std::distance(newnums.begin(), Upper);
  std::cout << "\nQuantity of 4s found: " << std::distance(Lower, Upper) << "\n";

  // can do the same using equal_range - get both upper and lower bounds
  // returns pair
  auto [Lower2, Upper2]{std::ranges::equal_range(newnums, 4)};
  assert(Lower2 == Lower);
  assert(Upper2 == Upper);
  std::cout << "Upper and lower bounds can be found at once using std::ranges::equal_range\n";
}

// ** The following are all linear search algorithms **

// 1
void find_algorithm(){
  // std::ranges::find
  // able to use with ranges, iterator/sentinal ranges, custom types
  // and projection functions. Returns first occurence

  // ex with iterators, custom type + projection function, overloaded  == operator in struct
  std::vector vec{CustomType{1}, CustomType{2}, CustomType{-3}, CustomType{3}, CustomType{5}};

  auto Projector{[](CustomType& x){ return CustomType(abs(x.value)); }};

  auto result{std::ranges::find(vec.begin(), vec.end(), CustomType{3}, Projector)};
  std::cout << "Found a struct with val " << result->value << " in position "<< std::distance(vec.begin(), result) << "\n";

  auto result2{std::ranges::find(vec.begin(), vec.end(), CustomType{6}, Projector)};
  if (result2 == vec.end()){
    std::cout << "A struct with val 6 or -6 was not found in the vector. Not safe to dereference\n";
  }
}

// 2
void find_if_algorithm(){
  // std::ranges::find_if
  // doesn't use == but passes each object into a predicate function we provide
  // also returns end iterator if does not find anything
  std::vector vec{CustomType{1}, CustomType{2}, CustomType{-3}, CustomType{4}, CustomType{5}};
  auto isEven{[](CustomType& x) { return x.value % 2 == 0; }};
  auto Result{std::ranges::find_if(vec, isEven)};
  auto Result2{std::ranges::find_if(Result+1, vec.end(), isEven)};
  
  std::cout << "Found an even struct with val " << Result->value  << " in position " << std::distance(vec.begin(), Result) << "\n";
  std::cout << "Found another even struct afterwards with val " << Result2->value  << " in position " << std::distance(vec.begin(), Result2) << "\n";
}

// 3
void find_if_not_algorithm(){
  // std::ranges::find_if_not
  // opposite of find_if
  std::vector vec{CustomType{1}, CustomType{2}, CustomType{-3}, CustomType{4}, CustomType{5}};
  auto isOdd{[](CustomType& x) { return abs(x.value) % 2 == 1; }};
  auto Result{std::ranges::find_if_not(vec.begin()+2, vec.end(), isOdd)};
  std::cout << "Found a not odd struct with val " << Result->value  << " in position " << std::distance(vec.begin(), Result) << "\n";
}

// 4 
void find_first_of_algorithm(){
  // std::ranges::find_first_of
  // want to find any of a range of possibilities
  std::vector Numbers{1, 2, 3, 4, 5};
  std::vector SearchTerms{0, 5, 1};
  auto Result{std::ranges::find_first_of(Numbers, SearchTerms)};
  std::cout << "Found a " << *Result << " in position "<< std::distance(Numbers.begin(), Result) << "\n";
}

// 5
void adjacent_find_algorithm(){
  // std::ranges::adjacent_find
  // returns iterator to the first object in a sequence whereq two adjacent objects are equal to each other
  std::vector Numbers{1, 2, 3, 4, 4, 5};
  auto Result{std::ranges::adjacent_find(Numbers)};
  if (Result != Numbers.end()){
    std::cout << "Two adjacent objects were found!\n";
  }

  std::cout << "Found two adjacent " << *Result << "s starting at position " << std::distance(Numbers.begin(), Result) << "\n";
}

// 6
void search_n_algorithm(){
  // std::ranges::search_n
  //  looks for a sequence of elements that match and equality chck
  // takes in range, number of sequential elements to search for, and the object to search for
  // returns the sequence as a subrange/view. The range will be empty if not found 
  // (can use .empty depending on the type of range the view is built on)

  // search for at least 2 sequential 4's.
  std::vector Numbers{1, 2, 3, 4, 4, 5};

  auto Result{std::ranges::search_n(Numbers, 2, 4)};
  if (Result.begin() != Result.end()){
    std::cout << "The subrange returned is not empty.\n";
  }
  std::cout << "Found two adjacent 4s starting at position " << std::distance(Numbers.begin(), Result.begin()) << "\n";
}

// 7
void search_algorithm(){
  // std::ranges::search
  // searches for the first matching subrange and returns a subrange/view
  // useful for strings
  std::string EmailAddress{"new-user@gmail.com"};
  std::string SearchString{"@gmail."};

  auto Result{std::ranges::search(EmailAddress, SearchString)};

  if (!Result.empty()) {
    std::cout << "User is using Gmail\n";
  }

  // but c++23 now supports this using the contains method for a cleaner API
  assert(EmailAddress.contains(SearchString));

  // currently std::search is the only algorithm where we can specify a custom searcher
  // std::default_searcher is used by default, we also have std::boyer_moore_searcher, std::boyer_moore_horspool_searcher
  // best searcher depends on context

  // ex.
  std::boyer_moore_searcher Searcher(SearchString.begin(), SearchString.end());
  auto Result2{std::search(EmailAddress.begin(), EmailAddress.end(), Searcher)};
  if (Result2 != EmailAddress.end()){
    std::cout << "Boyer Moore Searcher: User is using Gmail\n";
  }
}

// 8 
void find_end_algorithm(){
  // std::ranges::find_end
  // like std::search but searches in the opposite direction
  // will retrun last instance of the subsequence we are searching for
  std::vector Numbers{1, 2, 3, 1, 2, 3};
  std::vector Subsequence{1, 2, 3};

  auto Result{std::ranges::find_end(Numbers, Subsequence)};

  // still returns empty subrange if not found

  if (Result.begin()!= Result.end()) {
    std::cout << "Subsequence was found - result.begin() != result.end()\n";
  }

  if (Result.empty()) {std::cout << "Subsequence not found";
  } else {
    std::cout << "Found Subsequence: ";
    for (int& i : Result) {
      std::cout << i << ", ";
    }
    std::cout << "\nSubsequence starts at position " << std::distance(Numbers.begin(), Result.begin()) << "\n";
  }

}

int main(){
  constexpr bool run_find_algs = false;

  binary_search_algorithm();

  if constexpr (run_find_algs){
    find_algorithm();
    std::cout << "\n";

    find_if_algorithm();
    std::cout << "\n";

    find_if_not_algorithm();
    std::cout << "\n";

    find_first_of_algorithm();
    std::cout << "\n";
    
    adjacent_find_algorithm();
    std::cout << "\n";

    search_n_algorithm();
    std::cout << "\n";

    search_algorithm();
    std::cout << "\n";

    find_end_algorithm();
    std::cout << "\n";
  }
}