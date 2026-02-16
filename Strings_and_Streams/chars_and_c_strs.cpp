/*
Discussion of c-strings, raw-strings, and unicode

Compile using:
g++ chars_and_c_strs.cpp -o run
*/

#include <iostream>

int main(){
  // c-style string, null terminated
  const char* c_str{"Brian"};
  char b;
  std::cout << "Size of c-string ptr: " << sizeof(c_str) << " bytes\n";

  // raw strings treat \ as reg char
  std::string A{R"(\n \n \n \n \n \n )"};
  const char* B{R"(\n \n \t \t \t \n )"};
  std::cout << "Printing raw strings:\n";
  std::cout << A << "\n" << B << "\n";

  // different types of char
  char x{'x'};
  wchar_t y{'y'};
  char32_t z{'z'};

  std::cout << "Size of char " << sizeof(x) << " bytes\n";
  std::cout << "Size of wide char " << sizeof(y) << " bytes\n"; // compiler dependent
  std::cout << "Size of char32_t " << sizeof(z) << " bytes\n";

  // unicode char
  // may need to store as str if not enough bits
  const char* smiley{"😀"}; // U+1F600, requires 4 bytes to encode, 1 byte for null term
  std::cout << smiley << "\n";

}