/*
Introduction to using try blocks within functions
- with a focus on member initialization list exceptions
*/

#include <iostream>
#include <stdexcept>

// catch statements have to return proper return type
int Divide(int x, int y) {
  try {
    if (y == 0) {
      throw std::invalid_argument{
        "Cannot divide by zero"};
    }
    return x/y;  
  } catch (std::invalid_argument& e) {
    return -1;  
  }
}

int GetHealth(int Health) {
  if (Health < 0) throw std::logic_error{"Health cannot be negative"};
  return Health;
}


class Enemy {
public:
  Enemy(int Health) try: mHealth{GetHealth(Health)} {
    std::cout << "Entering the enemy's constructor" << std::endl;
  } catch (std::logic_error& e) {
    std::cout << e.what();
  }

 private:
  int mHealth;
};

int main() {
  try {
    // failed constructor, despite try statements in the constructor
    // implciity throws same exception that we have to catch
    Enemy Goblin { -100 };
  } catch (std::exception& e){
    std::cout << "\nGoblin construction failed: " << e.what() << std::endl;
  }
  std::cout << "Exceptions were caught\n";
  Divide(5, 4);
}