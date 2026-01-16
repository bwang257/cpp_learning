/*
Introduction to first class functions
- includes intro to function ptrs
*/


#include <iostream>
#include <format>

// c++ allows functions to be treated as variables, class members, return vals

class Book {
  public:
    bool issold() const { return false; }
    bool isAvailable() const {return true; }
    int getPrice() const { return 20; }
};

class BookStore {
  public:
    // predicate: a function that receives an argument and returns whether that arg satisfies some
    // condition

    bool all_of(auto predicate){ // auto only compiles in c++20
      return predicate(book1) && predicate(book2) && predicate(book3);
    }

  private:
    Book book1;
    Book book2;
    Book book3;
};


// callbacks
// function passed to another function
bool BookIsSold(const Book& b){
  return b.issold();
}

bool BookIsAvailable(const Book& b){
  return b.isAvailable();
}

bool MaxPrice15(const Book& b){
  return b.getPrice() <= 15;
}

// template functions can used in conjunction with 
// function pointers to provide additional flexibility
template <int max>
bool maxPrice(const Book& b){
  return b.getPrice() <= max;
}



int main(){
  BookStore bs;
  if (!bs.all_of(BookIsSold)){
    std::cout << "All books have not been sold\n";
  }
  if (bs.all_of(BookIsAvailable)){
    std::cout << "All books are still available\n";
  }
  if (!bs.all_of(maxPrice<15>)){
    std::cout << "All books are not under $15\n";
  }

  std::cout << "\nFunctions can be treated like other data types\n";
  std::cout << "Mem address of BookIsSold: " << (void*) &BookIsSold << "\n"; // need void so not implicitly converted to a bool

  bool (*bis_ptr)(const Book&) = nullptr; // how to write the function ptr type, use 'using' for readability
  bis_ptr = &BookIsSold;
  Book b;
  std::cout << std::format("Calling function through ptr: {}\n", (*bis_ptr)(b));
  bis_ptr = nullptr;
  if (bis_ptr){
    std::cout << "bis_ptr is no longer available\n";
  }

  // ** compiler can actually complete implicit referencing and dereferencing
  auto isav_ptr { BookIsAvailable };
  std::cout << std::format("Calling function through implicit de/referencing ptr: {}\n", isav_ptr(b));

}

// g++ -std=c++20 first_class_funcs.cpp -o run
