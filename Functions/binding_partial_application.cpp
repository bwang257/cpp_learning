/* 
Discussion of function binding and partial application
*/


#include <iostream>
#include <functional>
#include <string>

// functional binding is the process of creating
// a new callable by fixing some of the argument of
// an existing function to specific values

void someFunc(int x, int y, int z){
  std::cout << "The values of x, y, and z are: " << x << " " <<  y << " " << z << "\n";
}

class item {
  public:
    item(std::string name) : name{name} {}
    void buy(){
      std::cout << name << " has been bought!\n";
    }
    std::string name;
};

class Store{
  public:
    Store(std::string a_name = "mybook", std::string b_name = "mytoy", std::string c_name = "myfood") : 
      a{a_name}, b{b_name}, c{c_name} {};

    void for_each(auto callBack){
      callBack(a);
      callBack(b);
      callBack(c);
    }
    item a;
    item b;
    item c;
};

class Person {
  public:
    std::string name;
};

void buy_all(Person& buyer, item& item){
  std::cout << buyer.name << " has bought all of " << item.name << "!\n";
}


int main(){
  using namespace std::placeholders;

  // std::placeholders::_1, std::placeholders::_2, ... std::placeholders::_N
  auto Functor{std::bind(someFunc, 1, _1, _2)}; // placeholders for y and z
  Functor(2, 4);

  // bind_front() to bind leftmost arguments, c++20
  auto Functor2{std::bind_front(someFunc, 1, 2)};
  Functor2(8);

  // bind_back() does opposite, c++23
  auto Functor3{std::bind_back(someFunc, 1, 2)};
  Functor3(632);

  // can use placeholders to change order
  auto Functor4{std::bind(someFunc, _2, _3, _1)};
  Functor4(1, 2, 3);

  // binding for member functions
  item mybook{"The Sound and The Fury"};
  auto functor5{std::bind(&item::buy, _1)};
  functor5(mybook);

  // modern alternative in the use of lambdas
  auto myFunctor = [](int y, int z){ someFunc(1, y, z); };
  myFunctor(3, 6);

  // more complex example
  Store myStore{};
  Person brian{"Brian"};
  auto myFunctor2{std::bind(buy_all, brian, _1)};
  myStore.for_each(myFunctor2);
}