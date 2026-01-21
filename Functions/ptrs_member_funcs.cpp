/*
Exploration of pointers to member functions and data members
*/

// Static class members (attr + funcs) are defined once and shared among instances of the class
// one memory class, and can be accessed by using the class name as a namespace

// ptrs to non-static member functions are more complex
// because that must e called in the context of the instance of the class

#include <iostream>
#include <string>
#include <type_traits>
#include <format>


class Person{ 
  public:
    Person (std::string name) : name{name}{}

    std::string getName() {
      return name;
    }

    void setName(const std::string& newName) {
      name = newName;
    }

    // unable to do ptr to a private method so we provide a getter method
    static auto getPrivatePtr(){
      return &Person::PrivateMethod;
    }

    // virtual methods defined in base class, meant to be overriden in 
    // derived class
    virtual void walk(){
      std::cout << name << " is walking forward\n";
    }
  
  private:
    std::string name;
    void PrivateMethod(){
      std::cout << std::format("Calling {}'s private method\n", name);
    }
};

class TallPerson : public Person {
  public:
    TallPerson(std::string name, int height) : Person(name), height{height} {}
    void walk() override {
        std::cout << Person::getName() << " hit their head on the ceiling!\n";
    }
    int height;
    static int max_height;
};

int TallPerson::max_height{8}; 

int main(){

  using GetNamePtrType = std::string (Person::*)();
  GetNamePtrType Getter{&Person::getName};

  void (Person::*Setter)(const std::string&){&Person::setName};
  static_assert(std::is_member_pointer_v<decltype(Setter)>); // application of type traits

  // new .* operator
  // context_object.*pointer
  // invoke using (): (context_object.*pointer)()
  Person brian{"Brian"};
  std::cout << (brian.*Getter)() << "\n"; 
  (brian.*Setter)("Brian Wang");
  std::cout << (brian.*Getter)() << "\n"; 

  // if we only have a ptr to the object
  Person andrew{"Andrew"};
  Person* a_ptr{&andrew};

  // we can do this and just dereference
  std::cout << (*a_ptr.*Getter)() << "\n"; 
  // or use the ->* operator

  (a_ptr->*Setter)("Andrew E");
  std::cout << (a_ptr->*Getter)() << "\n";

  // many way to execute callables
  // std::invoke unifies them so that we dont have to define a bunch of templates/type traits
  // compatible with both member function ptrs and lambdas
  std::invoke(Setter, andrew, "andrew");
  std::cout << std::invoke(Getter, andrew) << "\n";


  // std::mem_fn() is a lightweight wrapper so that a pointer can be used with () operatoir
  auto getName{std::mem_fn(&Person::getName)};
  auto setName{std::mem_fn(&Person::setName)};
  setName(andrew, "Andrew, E.");
  std::cout << getName(andrew) << "\n";

  // using private method getter
  auto private_ptr{Person::getPrivatePtr()};
  Person Ben{"Ben"};
  std::invoke(private_ptr, &Ben);

  // ptrs to virtual methods
  auto v_ptr{&Person::walk};
  TallPerson bob{"Bob", 6};
  std::invoke(v_ptr, bob);

  // can also create ptrs to data members and even call them like functions
  auto h_ptr{&TallPerson::height};
  std::cout << "Bob's height: " << bob.*h_ptr << "\n";
  std::cout << std::invoke(h_ptr, bob) << "\n";

  // static data members simple
  int* max_ptr{&TallPerson::max_height};
  std::cout << "Max height: " << *max_ptr << "\n"; 

}


// g++ -std=c++20 ptrs_member_funcs.cpp -o run