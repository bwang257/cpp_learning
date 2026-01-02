/*
Introduction to class templates
- Class Template Argument Deduction (CTAD)
*/

// class templates (like std::pair) are essentially recipies for creating classes
// created at compile time. Creating templates is known as metaprogramming, writing code that writes code
// template arguments are provided in < >

#include <iostream>

using std::cout;
using std::endl;


// template arguments are evauated at compile time
// can be any expression but can't be a function with expressions determined at runtime

// when the template class is instantiated, everywhere the argument occurs is replaced with its value

// can add default values
// applies to structs as well (only difference between structs and classes is that class members are private by default)
template <typename T1 = int, typename T2 = int>
class myTriplet {
  // alternative implmentation where third is private
  public:
    T1 first;
    T2 second;
    myTriplet() = default;
    myTriplet(T1 first, T2 second) : first{first}, second{second} {}
    bool getThird() const {return third;}
    void setThird(bool newThird) {third = newThird;}
    

  private: 
    bool third;
};

template <typename T>
class someResource {
  public:
    T someField;
};



int main(){
  myTriplet<int, float> trip{42, 6.7f};
  trip.setThird(true);
  cout << "trip first: " << trip.first << "\n";
  cout << "trip second: " << trip.second << "\n";
  cout << "trip third: " << trip.getThird() << "\n";


  // Class Template Argument Deduction (CTAD)
  // compiler can automatically deduce type of class we need from our instantiation values
  // C++ 17 feature, may need to do -std=c++17

  // but: Use type deduction only if it makes the code clearer to readers who aren't familiar with the project - Google C++ style guide
  myTriplet trip2{42, 6.2f};
  cout << "CTAD works\n";

  // can nest paramters
  myTriplet<int, myTriplet<>> newTrip;
  myTriplet newTrip2;
  cout << "Can nest parameters and use template arguments (optionally without <>)\n";

  // CTAD can be used in a more advanced case where a class template Resource has a pair<T1, T2> field
  // this works: Resource SomeResource{Pair{9.8, 42}}
  
  // we may have no idea what type of data will be in our class template
  // C++ 20 CTAD feature, may need to do -std=c++20
  // compiler deduces T = myTriplet<int, float> and instantiates someResource<myTriplet<int, float>
  someResource r1{myTriplet{42, 6.7f}};
  someResource r2{"Hello World"};
  cout << "r2: " << r2.someField << endl;

  return 0;

}