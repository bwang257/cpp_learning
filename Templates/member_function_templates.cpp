/*
Introduction to member function templates
*/

#include <iostream>
#include <string>


class Monster{
  public:
    std::string name;
};

class Player {
  public:
    // member function template
    template <typename T>
    void Attack(T target){
      std::cout << name << " is attacking " << target.name << "." << std::endl;
    }
    std::string name;
};

// can create a member function template in template class
// member function hass access to template class instantiation parameters

enum class Style { Melee, Magic };

template <Style combatStyle>
class NewPlayer {
  public:
    template<typename t>
    void Attack(t target){
      std::cout << name << " is attacking " << target.name;
      if (combatStyle == Style::Melee ){
        std::cout << " with a sword." << std::endl;
      } else if (combatStyle == Style::Magic) {
        std::cout << " with spells." << std::endl;
      }
    }

    // can define a template member function from its implementation
    template <typename t>
    void Defend(t target);


    std::string name;
};

// see template_headers.* for implementing templates through hpp and ipp files
// implement template member function
template <Style s>
template <typename t>
void NewPlayer<s>::Defend(t target){
  std::cout << name << " is defending an attack from " << target.name;
  if (s ==  Style::Melee){
    std::cout << " with a sword." << std::endl;
  }
  else if (s == Style::Magic){
    std::cout << " with magic." << std::endl;
  }
  else {
    std::cout << std::endl;
  }
}


int main(){
  Player Brian{"Brian"};
  Player OtherPlayer{"Other Player"};
  Monster Blob{"Big Blob"};

  // the compiler can deduce which function needs to be instantiated
  Brian.Attack<Player>(OtherPlayer);
  Brian.Attack(Blob);

  // working with class template with member function template
  NewPlayer<Style::Melee> Andrew{"Andrew"};
  // Andrew.Attack<Player>(Brian);
  Andrew.Attack(Brian);
  NewPlayer<Style::Magic> Aman{"Aman"};
  Aman.Attack<NewPlayer<Style::Melee>>(Andrew);
  // Aman.Attack(Andrew);
  Aman.Defend(Andrew);
  return 0;
}
