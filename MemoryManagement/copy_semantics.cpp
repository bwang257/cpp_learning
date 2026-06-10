/* 
Shallow copying and deep copying
Introduction to return value optimization (RVO) as compiler optimizations
to reduce unnecessary copies
*/

#include <iostream>
#include <memory>


struct House {
  int size{10};
};

class Person {
  public:
    Person() : home {std::make_unique<House>()} {};
    ~Person() {
      home.release();
      std::cout << "Calling destructor!\n";
    };

    std::unique_ptr<House> home;

    // Default Copy Constructor provided by the C++ compiler looks like
    // Person (const Person& source) {
    //  home = source.home; <== copies the address only, does not create a new House struct
    // }
    // pass reference to the home too for deep copying (so that default isn't used)
    Person(const Person& source) : home{std::make_unique<House>(*source.home)}{
      std::cout << "(Person) Copy constructor called!\n";
    };

    // Default copy assignment operator implements shallow copying. 
    // Returns a reference to itself using *this
    // "this" is a pointer to the current object
    Person& operator=(const Person& source){

      // edge case where source = this
      if (this == &source){
        std::cout << "(Person) Copy assignment operator called on self!\n";
        return *this;
      }

      home = std::make_unique<House>(*source.home);
      return *this;
    }

    // Rule of Three
    // C++ convention that states if we define any of the following, we should define all of them
    // destructor, copy consturctor, copy assignment operator

};

struct myStruct {
  myStruct() = default;
  myStruct(const myStruct& source){
    std::cout << "Calling myStruct copy constructor\n";
  }
};

myStruct get_struct(){
  // technically should create myStruct A and return
  // a copy of A
  myStruct A;
  return A;
};

myStruct return_copy_struct(myStruct ms){
  // should technically copy when passed into function, copied in copy, and copied again when returned
  // note RVO compiler optimization
  myStruct copy{ms};
  return copy;
}

int main(){
  Person A;
  A = A;
  A.home->size = 20;

  // copy constructor
  Person B{A};

  // copy assignment operator
  Person C;
  C = A;

  // Shallow Copying --> only the pointer is copied if the default constructor is called
  // Deleting Person A's home will also destroy Person B's home
  // This leads to a double-free error (assuming raw pointers are used)
  std::cout << "Person A's home address: " << A.home << '\n';
  std::cout << "Person A's home size: " << A.home->size << '\n';
  std::cout << "Person B's home address: " << B.home << '\n';
  std::cout << "Person B's home size: " << B.home->size << '\n';
  std::cout << "Person C's home address: " << C.home << '\n';
  std::cout << "Person C's home size: " << C.home->size << '\n';

  // Compilers are able to eliminate unncessary copying
  // this is known as return value optimization or RVO
  std::cout << "\nCalling get_struct" << '\n';
  myStruct D = get_struct();
  std::cout << "Get struct done" << '\n';

  // calling return_copy_struct() requires 3 different copies of our object
  // in memory, waste of resources
  std::cout << "\nCalling return_copy_struct" << '\n';
  D = return_copy_struct(D);
}