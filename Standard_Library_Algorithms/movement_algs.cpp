/*
Discusses standard library movement algorithms
- all of thiese algorithms you are able to provide an iterator-sentinel pair 
  instead of a range
- if pre c++20, can exclude ranges qualification 
  - note that std::move in this context is in <algorithm>
    while move semantics std::move is in <utility>
*/

#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
#include <random>

class Book{
  public:
    Book() : title{"Default Book"} {} 
    Book(std::string title) : title{title}{}
    Book(const Book& original) = default; // copy constructor

    Book(Book&& source) : title{std::move(source.title)} {
      std::cout << "Move constructor called!\n";
    }

    // move assignment operator
    Book& operator=(Book&& source){
      if (&source != this){
        title = source.title;
        source.title += " (Moved)";
      }
      return *this;
    }

    std::string getTitle() const {
      return title;
    }

    std::string title;
};

struct T { 
  int value;
  T(int value) : value {value}{}
  T(const T& source) = default;
  T& operator=(T&& source) noexcept {
    value = source.value;
    source.value = 9999;
    return *this;
  }
};

void stl_move(){
  // std::ranges::move
  // use for moving objects left
  // moves objects from a source range to a destination range
  // returns struct with in (setinel for source range) and out
  // ptr to position after last element moved 
  using namespace std::string_literals;
  std::vector<Book> shelf1{"Book1"s, "Book2"s, "Book3"s, "Book4"s, "Book5"s};
  std::vector<Book> shelf2{shelf1.size()+2}; // this requires default constructor for Book

  // takes in input range and iterator where to being adding element
  // ** performs element-wise move assignment so we need to use custom  move assignment operator **
  auto [in, out] = std::ranges::move(shelf1, shelf2.begin());
  std::cout << "Books in shelf1 (source):\n";
  for (auto& book : shelf1){
    std::cout << book.getTitle() << "\n";
  }

  std::cout << "\nBooks in shelf2 (destination):\n";
  for (auto& book : shelf2){
    std::cout << book.getTitle() << "\n";
  }

  std::cout << "\nThe input had " << std::distance(shelf1.begin(), in) << " objects\n";
  std::cout << "The output iterator is at index " << std::distance(shelf2.begin(), out) << "\n";
  std::cout << "\n";

  // if destination iterator within input range, behavior of move() and move_backwards() undefined
}

void stl_move_backwards(){
  // std::ranges::move_backwards
  // use for moving objects right
  // essentially does the same thing but we provide an iterator to where we want insertion to end
  // maintains the relative order of the elements
  // iterator needs to be bidirectional
  // [in, out]: in points to sentinel in input range (ex. source.end()), 
  // out to leftmost element in input range in destination range
  std::vector Source{1, 2, 3};
  std::vector Destination{0, 0, 0, 0, 0};

  std::ranges::move_backward(Source, Destination.end());

  std::cout << "Values in Destination: ";
  for (auto& Num : Destination) {
    std::cout << Num << ", ";
  }
  std::cout << "\n";
  std::cout << "\n";
  // if destination iterator within input range, behavior of move() and move_backwards() undefined
}

void stl_rotate(){
  // std::ranges::rotate
  // takes in range and an iterator pointing to what will become the new first element in the range
  // returns a subrange view of the oriignal range
  
  std::vector Days{"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
  auto Subrange{std::ranges::rotate(Days, Days.end() - 1)};

  for (auto& Day : Days) {
    std::cout << Day << ", ";
  }
  std::cout << "\n";
  std::cout << "Subrange has " << Subrange.size() << " elements (" << Subrange.front() << " - " << Subrange.back() << ")\n";
}

void swap(T& A, T& B){
  std::cout << "Swapping " << A.value << " and " << B.value << "\n";
  std::swap(A.value, B.value);
}

void stl_reverse(){
  // std:::ranges::reverse
  // reverse order of elements in place
  // first tries to find a swap() function to call about center of container
  // otherwise falls back to move semantics, or copy semantics otherwise
  std::vector Nums{T{1}, T{2}, T{3}, T{4}, T{5}};
  std::ranges::reverse(Nums);
  std::cout << "Numbers after reversing: ";
  for (auto& num : Nums){ std::cout << num.value << ", "; }
  std::cout << "\n";
}


void stl_shuffle(){
  // std::ranges::shuffle
  // takes in container to shuffle and an RNG engine to use
  std::vector Range{1,2, 3, 4, 5, 6};
  std::random_device Device;
  std::mt19937 Generator{Device()};

  std::ranges::shuffle(Range, Generator);
  std::cout << "Shuffled Numbers: ";
  for (auto& Num : Range) {
    std::cout << Num << ", ";
  }
  std::cout << "\n";
}

// c++23
// NOTE: MY COMPILER DID NOT SUPPORT THIS, THERE MAY BE ISSUES IN THIS CODE
// std::ranges::shift_left does exactly what you think it does
void stl_shift_left(){
  // std::ranges::shift_left
  // takes in a range and the number of steps n to shift by
  // overwrites first n elements and keeps last n elements in their
  // "moved_from" state

  // std::vector Range{1, 2, 3, 4, 5, 6};
  // std::cout << "Shifting left 2 steps: ";
  // for (auto& Num : Range) {
  //   std::cout << Num << ", ";
  // }
  // std::cout << "-> ";
  // std::ranges::shift_left(Range, 2);
  // for (auto& Num : Range) {
  //   std::cout << Num << ", ";
  // }
  // std::cout << "\n";

  // applying custom move assignment function where
  // movefrom state set to 9999
  // std::vector Range2{T{1}, T{2}, T{3}, T{4}, T{5}, T{6}};

  // std::cout << "Shifting left 2 steps: ";
  // for (auto& Num : Range2) {
  //   std::cout << Num.value << ", ";
  // }
  // std::cout << "-> ";
  // std::ranges::shift_left(Range2, 2);
  // for (auto& Num : Range2) {
  //   std::cout << Num.value << ", ";
  // }
  // std::cout << "\n";

  // Returns a subrange view that excludes the moved-from elements
}

// c++23
// not supported by my compiler
void stl_shift_right(){
  // std::ranges::shift_right
  // does exactly what you think it does (opposite of shift_left)
}

int main() {
  stl_move();
  stl_move_backwards();
  stl_rotate();
  stl_reverse();
  stl_shuffle();
  stl_shift_left();
  stl_shift_right();
}