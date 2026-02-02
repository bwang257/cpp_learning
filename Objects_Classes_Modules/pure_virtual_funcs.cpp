/*
Pure Virtual Functions / Abstract Classes + Interfaces
*/

// some classes we create we use for inheritance but we never expect to 
// actually instantiate objects. --> we use pure virutal functions to define abstract classes

// C++ technically does not have interfaces but an abstract class with only pure
// virtual functions is essentially an interface - multiple inheritance can then be applied

#include <iostream>
#include <string>
#include <vector>

// no longer able to create objects from this class
// if a function does not override say_hello, it will also be abstract
class Character {
  public:
    virtual std::string say_hello() = 0; // assign 0 to create pure virtual func
};

// also abstract
class Fish : public Character {};

// but can define a default implementation that needs to be explicitly called
std::string Character::say_hello(){
  return "Default hello\n";
}

class ClownFish : public Fish {
  public:
    std::string say_hello() override {
      return Character::say_hello(); // explicitly confirm if developer good with default implementation
    }
};

class Shark : public Fish {
  public:
    std::string say_hello() override{
      return "Grrrunt\n"; // what does a shark say?
    }
};

class Human : public Character {
  public:
    Human() : name{"Brian"} {};
    Human(std::string name) : name{name} {};
    std::string say_hello() override{
      return "Hi! My name is " + name + "\n";
    }
    std::string name;
};


void greet(Character& obj){
  std::cout << obj.say_hello();
}

int main(){
  Human aman{"Aman"};
  ClownFish cf;
  Shark jeff;

  greet(aman);
  greet(cf);
  greet(jeff);
}