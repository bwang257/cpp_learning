/*
Converntion of using .cppm for a module interface file is becoming more common
*/

export module customModule;

import <iostream>;

// public
export namespace customModule{
void SayHello(){
  std::cout << "Hello from customModule\n";
};
};

// private
constexpr float Pi{3.14}; 