/*
Introduction to template specialization
*/

#include <iostream>
#include <string>
#include "template_specialization.hpp"

struct Rock {
  std::string description{"Rock"};
};

struct Person {
  std::string name{"Bob"};
};

// the functions below can also be in a class as member functions too
// can also overload the function in another file
// General Template Function
template <typename T>
void Render(T subject){
  std::cout << "Rendering a " << subject.description << std::endl;
}

// Specialized Template Function
template <>
void Render<Person>(Person subject){
  std::cout << "Rendering " << subject.name << std::endl;
}

// Can also simply use if constexpr and std::same_as
// this is a c++20 feature
template<typename T>
void revisedRender(T subject){
  if constexpr (std::same_as<T, Person>){
    std::cout << "Revised Rendering of " << subject.name << std::endl;
  }
  else {
    std::cout << "Revised Rendering of a " << subject.description << std::endl;
  }
}

// class template specialization
template <typename T, int qty>
class Container {
  public:
    void Render(){
      std::cout << "General Container is rendering " << qty << " " << object.description << "s" << std::endl;
    }
    T object;
};

// specialized class templates
// when we specialize a template, we don't have to specify every parameter
// partial template specialization only specifies a subset of every parameter 

// ex. of full specialization
template <>
class Container<Person, 1>{
  public:
    void Render(){
      std::cout << "Specialized Container is rendering a single " << subject.name << std::endl;
    }
    Person subject;
};

// ex. of partial specialization
template <int qty>
class Container<Person, qty>{
  public:
    void Render(){
      std::cout << "Specialized Container is rendering many " << subject.name <<  "s" << std::endl;
    }
    Person subject;
};

// specialize template library by telling SomeLibrary how to get our object's names
namespace SomeLibrary {
  template<>
  std::string GetName<Rock>(Rock& rock){
    return rock.description;
  }
}

int main(){
  Render(Person{});
  Render(Rock{});
  revisedRender(Person{});
  revisedRender(Rock{});

  Container<Person, 1> cont1{Person{}};
  Container<Person, 5> cont2{Person{}};
  Container<Rock, 2> cont3{Rock{}};
  Container<Rock, 1> cont4{Rock{}};
  cont1.Render();
  cont2.Render();
  cont3.Render();
  cont4.Render();

  Rock rock{"big rock"};
  SomeLibrary::Process(rock);
  return 0;
}

