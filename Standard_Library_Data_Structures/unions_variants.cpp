/*
Introduction to constrained dynamic types using unions and std::variant
- also includes intro to the visitor pattern and application of variant type traits
*/


#include <iostream>
#include <variant>
#include <string>


// unions add ability to store var of dynamic type, 
// without using unnecessary memory
union NumberUnion {
  double d;
  int i;
};

// create a type you can't call a constructor on
struct T {
  T() = delete;
};

class Character{
  public:
    Character(std::string name) : name{name} {}
    std::string name;
};

// for visitor pattern where we separate algorithms from the objects 
// those algorithms work on

// implements several simple algorithms
struct Visitor {
  void operator()(int i){
    std::cout << "It's an integer: " << i << '\n';
  }
  void operator()(float i){
    std::cout << "It's a float: " << i << '\n';
  }
  void operator()(bool i){
    std::cout << "It's a bool: " << i << '\n';
  }
  void operator()(const std::monostate&){
    std::cout << "It's empty\n";
  }
  void operator()(const T&){
    std::cout << "It's a T\n";
  }
};


// variant type traits eval at compile time
template <typename T> 
void Handle(T Variant){
  if constexpr (std::is_same_v<std::variant_alternative_t<0, T>, int>) {
    std::cout << "The first type is an int\n";
  }
  if constexpr (std::is_arithmetic_v<std::variant_alternative_t<1, T>>) {
    std::cout <<"The second is arithmetic\n";
  }
  if constexpr (std::is_convertible_v<std::variant_alternative_t<2, T>, int>) {
    std::cout <<"The third is convertible to an int\n";
  }
  if constexpr (std::variant_size_v<T> == 3){
    std::cout << "There are 3 alternatives in this variant\n";
  }
}


int main(){
  NumberUnion Number;
  // allocates memory to fit largest type
  std::cout << "Size of double/int union: " << sizeof(Number) << " bytes\n";

  // the native implementation of unions is not type-safe
  Number.d = 9.8;
  Number.i = 95; // int becomes the active type
  std::cout << std::format("No compiler protection (undefined behavior):\nNumber.d: {}, Number.i: {}\n", Number.d, Number.i);

  // thus we use variants (aka alternatives)
  std::variant<int, float, Character> myVariant;
  std::cout << "Variant initialized to default constructor of first type: " << std::get<int>(myVariant) << std::endl;
  // can directly reassign
  myVariant = 42;
  myVariant.emplace<Character>("Brian");
  myVariant.emplace<2>("Andrew"); // can also pass in index of the type
  
  // get current value
  std::cout << "Variant curr value: " << std::get<Character>(myVariant).name << "\n";

  // safe guards 
  try {
    std::get<int>(myVariant);
  } catch (const std::bad_variant_access& e){
    std::cout << "Error getting variant int value: " << e.what() << "\n";
  }
  // can also work with ptrs
  myVariant = 9.8f;
  auto ptr = std::get_if<float>(&myVariant); // null ptr if not a float 
  if (ptr){
    std::cout << "Able to get float value from variant of " << *ptr << "\n";
  }
  else {
    std::cout << "Float access failed\n";
  }

  // can get current type
  if (std::holds_alternative<float>(myVariant)){ std::cout << "The variant is currently holding a float ..."; }
  if (!std::holds_alternative<int>(myVariant)){ std::cout << "and not an int. "; }
  std::cout << "Its float type is of type index " << myVariant.index() << "\n"; // can get index of the type used

  // visitor pattern
  std::variant<int, float, bool> Variant{3.14f};
  std::visit(Visitor{}, Variant); // Visitor is a functor here

  // comparing variants
  // if same type, compare the value
  std::variant<int, float, bool> Variant2{3.5f}; // needs to be the same variant type <int, float, bool>
  if (Variant2 > Variant){ std::cout << "The two float variants can be compared\n"; }
  Variant2 = true;
  if (Variant2 > Variant){ std::cout << "The variants are compared by their type index if they do not store the same type (2 > 1)\n"; }

  // if first type does not have a constructor, we can use
  // std::monostate --> denote an "empty" type for use in variants
  std::variant<std::monostate, T, bool> newVariant;
  std::visit(Visitor{}, newVariant);

  // empty Variant methods
  if (Variant.valueless_by_exception()) {
    std::cout << "Variant is valueless\n";
  }

  // returns val equal to std::variant_npos
  if (Variant.index() == std::variant_npos) {
    std::cout << "index() returned npos\n";
  }

  try {
    std::get<bool>(Variant); 
  }  catch (const std::bad_variant_access& e) {
    std::cout << "std::get threw exception when trying to access a bool\n";
  }

  std::variant<int, float, bool> typeTraitVariant;
  Handle(typeTraitVariant);
}


