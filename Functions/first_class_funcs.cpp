/*
Introduction to first class functions
*/


#include <iostream>

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


int main(){
  BookStore bs;
  if (!bs.all_of(BookIsSold)){
    std::cout << "All books have not been sold\n";
  }
  if (bs.all_of(BookIsAvailable)){
    std::cout << "All books are still available\n";
  }
  if (!bs.all_of(MaxPrice15)){
    std::cout << "All books are not under $15\n";
  }
  
}