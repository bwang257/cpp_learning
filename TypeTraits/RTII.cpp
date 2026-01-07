/*
Introduciton to Run-Time Type Information (RTTI)
- typeid()
- dynamic casting
*/

#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <string>

/*
Supporting RTII requires compilers too insert additional data into our
compiled binary, describing our types. Thus, optional optimization
is to disable RTII entirely (dynamic cast + typeid)
*/

// to do run time type deduction without RTTI we can:
enum class MonsterType {Monster, Dragon};

class Monster{
  public: 
    virtual MonsterType getType() const {
      return MonsterType::Monster;
    }
};

class Dragon : public Monster {
  MonsterType getType() const override {
    return MonsterType::Dragon;
  }
};

void downcastFunction(Monster& Enemy){
  Dragon* dragonPtr{dynamic_cast<Dragon*>(&Enemy)};
  if (dragonPtr){
    std::cout << "Downcast found a dragon!\n";
  }
  // we can use the enum class and static cast once we have 
  // confirmed the type instead
  // if (Enemy.getType() == MonsterType::Dragon){
  //   Dragon* dragonptr{static_cast<Dragon*>(&Enemy)};
  // }
}

void typeIdFunction(Monster& Enemy){
  if (typeid(Enemy) == typeid(Dragon)){
    std::cout << "typeid found a dragon!\n";
  }
}


// note would not make sense to compare non-polymorphic template types
// because they are instantiated at compile time and should be compared using
// if constexpr and std::same_as

int main(){
  // typeid reqturns a std::type_info object
  int x = 42;
  std::string y = "Hello";
  std::cout << "42 has type " << typeid(x).name() << std::endl;
  std::cout << "'Hello' has type " << typeid(y).name() << std::endl;
  
  // comparing types at runtime
  if (typeid(int) == typeid(x)){
    std::cout << "x is an int" << std::endl;
  }
    if (typeid(std::string) == typeid(y)){
    std::cout << "y is a string" << std::endl;
  }

  // using typeid can be slightly better for performance
  // if we do not need to access the class's members
  Dragon drag;
  Monster monst;
  downcastFunction(drag);
  downcastFunction(monst);
  typeIdFunction(drag);
  typeIdFunction(monst);

  // typeid returns std::type_info objects that can't be copied
  // for flexibility, C++ has a std::type_index type constructible from std::type_info
  int Number{42};
  std::type_index TypeInfo{typeid(Number)};
  std::cout << "42 is an " << TypeInfo.name() << std::endl;

}



