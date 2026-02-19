/*
Scoped and unscoped enums in C++

g++ -std=c++14 enums.cpp -o run
*/

#include <iostream>
#include <tuple>

// forward declarations mentioned because if an enum is changed
// the whole system does not have to be recompiled. 

void unscoped_enum(){
  // names of enums belong to same scope containing the enum
  // int price{1}; // can't do this

  // unscoped enums can only be declared when specfiying the underlying type:
  enum Status: std::uint8_t;

  enum metrics {price, volume, high, low};

  // default indexed starting at 0
  std::cout << "Index of volume: " << volume << "\n";

  // makes accessing tuple elements more readable
  auto data_point = std::make_tuple(53, 123, 68, 40);
  std::cout << "High: " << std::get<high>(data_point) << "\n";

  // but because unscoped enums implicitly convert to integral types
  if (price < 1){
    std::cout << "I am comparing an unscoped enum to an int\n";
  }
}

// if after C++17, could just do <auto E>
template <typename Enumtype, Enumtype E>
constexpr auto to_index(){
  return static_cast<std::size_t>(E);
}

// using std::underlying_type to get underlying value
template<typename Enumtype>
constexpr auto to_UType(Enumtype enumerator) noexcept {
  return static_cast<typename std::underlying_type_t<Enumtype>>(enumerator);
}


void scoped_enum(){
  // can be forward declared and do not leak scope
  // no implicit type conversion to underlying type though
  enum class metrics {price, volume, high, low};

  auto data_point = std::make_tuple(53, 123, 68, 40); 
  constexpr size_t volume_idx = to_index<metrics, metrics::volume>(); // verbosity that auto could have eliminated
  std::cout << "Volume: " << std::get<volume_idx>(data_point) << "\n";

  enum class Status : uint8_t {
    Sucess = 0,
    NotFound = 44,
    Error = 255
  };

  if (static_cast<int>(Status::NotFound) < 45){ // uint_t --> int through integer promotion mechanism
    std::cout << "I can only compare a scoped enum to an int if I cast it\n";
  }

  auto err_code = to_UType(Status::Error);
  // since uint8_t is typically typedef for unsigned char, it tries to print ASCII for 255, need cast
  std::cout << "Error code: " << static_cast<int>(err_code) << "\n";
  static_assert(std::is_same<decltype(to_UType(Status::Error)), uint8_t>::value, "");
}

int main(){
  unscoped_enum();
  scoped_enum();
}