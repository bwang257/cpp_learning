/*
Introduction to SFINAE to control overload resolution
- abbrev. for Substitution Failure is Not An Error
*/

// allows templates to remove themselves from consideration during overload
// resolution if their arguments do not meet certain reqs

// if error occurs instantiating a template, compiler will not throw error
// and simply remove the template from the candidates list

#include <iostream>
#include <type_traits>



// SFINAE --> complex and inelegant solution
// note that void pointers are valid in C++
template <typename T>
void Render(T obj, decltype(obj.Render())* y = nullptr){
  std::cout << "Template Function Called\n";
  obj.Render();
}

void Render(float x){
  std::cout << "Non-Template Function Called\n";
  std::cout << "Rendering a float: " << x << '\n';
}

struct Rock {
  void Render(){
    std::cout << "Rendering a rock\n";
  }
};

// instead can use std::enable_if
// accepts a boolean and a type, returns struct if true
// will throw compilation error if we try to use it
// more elegant solution to SFINAE
template <typename>
struct is_edible : std::false_type {};

template <typename T>
constexpr bool is_edible_v{is_edible<T>::value};

struct Chicken {
  void eat(){
    std::cout << "Eating a chicken\n";
  }
};

template <>
struct is_edible<Chicken> : std::true_type {};

void eat(float x){
  std::cout << "Struggling to eat a float: " << x << std::endl;
}

template<typename T, std::enable_if_t<is_edible_v<T>, int> = 0>
void eat(T x){
  x.eat();
}

int main(){
  Render(3.14); // double
  Render(Rock{});

  eat(3.14);
  eat(Chicken{});
  return 0;
}