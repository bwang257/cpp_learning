/*
String views

g++ -std=c++17 string_views.cpp -o run
*/

#include <iostream>
#include <string_view>

// string views allow for read only interfaces for a string
// prevents unnecessary copying when a char* is passed as a function arg

void HandleString(const std::string& Input){
  // std::cout << Input << "\n";
}

void view_overview(){
  HandleString("Passing String literal as an argument - unnecessary copying. We should use a string view"); // string literal, chars must be copied into const reference, unnecessary

  std::string_view test;
  std::cout << "Size of a string view (just a const char* and a size_t length): " << sizeof(test) << " bytes\n";

  using namespace std::string_view_literals;
  // instantiate using string_view literal, c-style string, string literals, and iterator pair
  // string_view is technically std::basic_string_view<char> --> can also do std::wstring_view or std::basic_string_view<wchar_t>
  std::string_view sview{"String view created from string view literal"sv}; 

  // we need to be careful about dangling string views
  // creating string_views through a returned std::string or string literal will deallocate the std::string
  // leading to undefined --> use sv literal or c-style strings which have static duration
  std::string_view sview2{"String view created from string literal."};
  std::string_view badview = std::string("temporary"); // don't do this!

  // const / constexpr
  // const does not allow reassignment, constexpr should be used as modern constexpr string
  sview = sview2;
  constexpr std::string_view sview3{"Hello"};

  // string_view --> std::string
  // can't be done implcitly, requires static cast
  HandleString(static_cast<std::string>(sview2));

  // string_view --> c-style string
  // if can't be sure that our view is null terminated:
  HandleString(std::string(sview3).c_str());
  
  std::cout << "\n";
}

int main(){
  view_overview();
}