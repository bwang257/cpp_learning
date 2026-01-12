/*
More about std::pair template
*/

#include <iostream>
#include <utility>


// as a pair is a type of tuple
template <typename T>
void HandlePair(T tuple){
  // First Type: can do:
  T::first_type;
  std::tuple_element<0, T>::type; // where T is the type of object we are querying
  std::tuple_element_t<0, T>;

  // second type
  T::second_type;
  std::tuple_element<1, T>::type;
  std::tuple_element_t<1, T>;
}

int main(){
  // limited to two values but is a heterogeneous container - different types
  // pair is essentially a std::tuple with only two objects
  std::pair<int, int> myPair{4, 5};

  // can also call make_pair function
  auto myPair2{std::make_pair(42, true)};
  // or for C++17+ (since we have CTAD)
  auto myPair3{std::pair(42, true)};

  // accessing members
  std::cout << "myPair: " << myPair.first << ", " << myPair.second << '\n';
  // enter index, can use for any container
  std::cout << "myPair2: " << std::get<0>(myPair2) << ", " << std::get<1>(myPair2) << '\n';
  // or if types are different
  std::cout << "myPair3: " << std::get<int>(myPair2) << ", " << std::get<bool>(myPair2) << '\n'; // enter type

  // use fo structured binding operator
  std::pair Player{"Anna", 40};
  auto [Name, Level]{Player};
  std::cout << "Name: " << Name << ", Level: " << Level << '\n';

  // can also find the types of the objects in the pair (use in template for ex.)
  std::cout << "First Type: " << typeid(std::pair<std::string, int>::first_type).name() << '\n';
  std::cout << "Second Type: " << typeid(std::pair<std::string, int>::second_type).name() << '\n';

}