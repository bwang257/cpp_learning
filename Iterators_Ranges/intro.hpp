// intro.cpp header file defining custom classes with range

#pragma once
#include <iostream>
#include <vector>
#include <type_traits>

class Person{
  public:
    Person(std::string name) : name{name} {
      std::cout << "Creating person " << name << "\n";
    }

    Person(const Person& orig) : name{orig.name}{
      std::cout << "Copying " << this->name << "\n";
    }
    Person(Person&& orig) : name{std::move(orig.name)}{
      std::cout << "Moving " << this->name << "\n";
    }
    std::string name;
};


template <typename T1>
class Party{
  public:
    Party(int size = 10){
      members.reserve(size);
    }

    template <typename... types>
    void add_member(types&&... args) {
      members.emplace_back(std::forward<types>(args)...);
    }

    std::vector<T1>::iterator begin(){
      return members.begin();
    }
    std::vector<T1>::iterator end(){
      return members.end();
    }

  private:
    std::vector<T1> members;
};

