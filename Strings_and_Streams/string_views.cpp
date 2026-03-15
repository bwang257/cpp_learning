/*
String views

g++ -std=c++23 string_views.cpp -o run
*/

#include <iostream>
#include <string_view>
#include <ranges>
#include <regex>
#include <cassert>
#include <cstring>

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

void view_methods(){
  std::string_view String{"Hello World"};
  std::string_view View{String.begin(), String.begin() + 5};
  assert(View.size() == 5); // num chars the string view corresponds to

  // can directly index [], use .at(), and front (first char) and back (last char) methods
  // can also compare, but equal comparisons generally should be done using enum classes

  assert(View.contains("Hello"));
  assert(View.starts_with("Hel"));
  assert(View.ends_with("lo"));
  assert(View.find("lo") == 3); // returns index of first occurrence
  assert(View.find("l", 3) == 3); // customize where our search starts
  assert(View.rfind("llo") == 2); // rfind searches in reverse order

  size_t pos{View.find("NotInString")};
  assert(pos == std::string::npos); // find and rfine returns a token equal to npos if not found

  // take in string, return index that match/not match any of those chars
  assert(View.find_first_of("Hel") == 0);
  assert(View.find_first_not_of("Hel") == 4);
  // similarly we have find_last_of and find_last_not_of that search from the end of the string view

  // can use string views with other views
  std::string_view name{"Brian"};
  std::cout << "Printing the first 3 chars of my name: ";
  for (char c : std::views::take(name, 3)){
    std::cout << c << ", ";
  }
  std::cout << "\n";

  using std::views::iota, std::views::zip;
  for (auto T : zip(iota(1), name)){
    std::cout << "Char " << std::get<0>(T) << ": " << std::get<1>(T) << "\n";
  }

  // shrinking a string view - does not modify the underlying 
  std::string_view alph{"abcdef"};
  std::string_view letters{alph};
  letters.remove_prefix(1);
  letters.remove_suffix(2);
  assert(letters == "bcd");

  // copying chars: takes in raw ptr to char array, num chars, and pos of first char to copy (default 0)
  char Output[10]{"---------"};
  alph.copy(Output + 2, 6);
  assert(strcmp(Output, "--abcdef-") == 0);

  // note that can also use with regex using iterators
  // below is just a simple example
  std::string_view Input{"Hello world"};
  std::regex Pattern("hello", std::regex_constants::icase);
  bool matchResult{std::regex_search(Input.begin(), Input.end(), Pattern)};
  assert(matchResult);

  std::cout << "\n";
}


int main(){
  view_overview();
  view_methods();
  std::cout << "All assertions passed\n";
}