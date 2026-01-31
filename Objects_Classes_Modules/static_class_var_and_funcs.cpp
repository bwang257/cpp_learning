/*
Static Class Variables and Functions
*/

// similar to namespace so we should focus on using classes
// only if we intend to instantiate objects unless most intuitive to group
// static var in a class

#include <iostream>
#include <string>
#include <vector>


// If I want a objects of a class to all share the same var
// same var shared across all objects of that class
// define static inline (if class used across multiple files,
// we need inline to avoid multiple definitions

// avoid static var being changed using const

class book{
  public:
    book(std::string title) : title{title}{} 
    const static inline std::string material{"Paper"};
    static inline int price{10};
    std::string title{"Default"};
};

// static var can be constexpr, (can remove inline because thats implied by constexpr)
// this is because class is known at compile time, normally var are only known at run time instantiation

// static functions do not read or write to the object's properties unless they are static too
// can call other static funcs
class store{
  public:
    store(){
      books.emplace_back("Book 1");
      books.emplace_back("Book 2");
      books.emplace_back("Book 3");  
    }

    static inline int get_max_books(){
      return max_books;
    }
  
    constexpr static double profit_margin{0.2};
    std::vector<book> books;
  private:
    static inline int max_books{15};
};


int main(){
  book a{"A"};
  book b{"b"};
  if (&b.price == &a.price){
    std::cout << "Book price memory address is same\n";
  }
  a.price*=2;
  std::cout << "Doubling book a's price leads book b's price to be: " << b.price << "\n";

  // can access static var without class instantiation
  std::cout << "book store has margin of " << store::profit_margin << "\n";
  std::cout << "calling get max books: " << store::get_max_books() << " books\n";
}
