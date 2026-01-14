/*
Unconstrained dynamic types using void pointers and std::any
- type safety containers for void ptr, runtime tpye checking
*/

// note that c++ is a statically typed language - unconstrained dynamic types
// especially outside of compile time templates and std::variant should be quite rare
// - arbitrary user data, developer tools (ex IDE), message passing

#include <iostream>
#include <any> // c++17
#include <string>

class Person {
  public:
    Person(std::string name, int age) : name{name}, age{age} {}
    std::string name;
    int age;
};



int main(){
  void* ptr; // ptr to any type of data, can be null
  double d = 9.8;
  int i = 7;
  bool b = true;

  ptr = &b;
  ptr= &d;
  
  // cannot directly dereference a void ptr
  std::cout << "the void pointer currently points to a double: " << *static_cast<double*>(ptr) << "\n";
  

  // compiler offers no safety checks
  std::cout << "but we can still cast it to a int ptr: " << *static_cast<int*>(ptr) << "\n";

  // type safety implemented through std::any, essentially a container
  std::any someData{32}; // init with int
  someData = true;
  someData = Person{"Andrew", 20};
  auto moreData{std::make_any<Person>("Brian", 19)}; // template type + constructor args
  moreData.emplace<Person>("Ben", 19); // similar for emplace

  moreData.reset(); // destroys the obj held by the any container
  if (!moreData.has_value()){
    std::cout << "moreData does not have a val after being reset\n";
  }

  moreData = Person{"Matthew", 20};
  // accessing values
  try {
    std::cout << "moreData now stores data for " << std::any_cast<Person>(moreData).name << "\n";
  } catch (const std::bad_any_cast& e){
    std::cout << "That was not a person: " << e.what() << "\n";
  }



  // run time type checking
  if (moreData.type() == typeid(Person)) {
    std::cout << "myData stores a person now\n";
  }
  moreData = 5;

  if (moreData.type() == typeid(int)) {
    std::cout << "myData stores an int now\n";
  }

  moreData.reset();
  // empty any container has typeid void
  if (moreData.type() == typeid(void)) {
    std::cout << "It's empty\n";
  }








}