/*
Deeper dive into std::string objects

Compile using:
g++ std_string.cpp -o run
*/

#include <iostream>
#include <string>

int main(){
  // std::string_literals creates a std::string directly
  using namespace std::string_literals;
  std::string str{"Hello\0world"s}; 
  std::cout << str << "\n";

  std::string str2{"Hi\0world"}; // iniitalize with c str constructor
  std::cout << str2 << "\n";

  // concatenate using + operator
  str2 += " world";
  std::cout << str2 << "\n";


  // copies of strings are deep copies

  // std::string functions
  std::cout << "Length of str: " << str.length() << "\n";
  
  if (str != str2){
    std::cout << "str and str2 are not equal. ";
  }
  if (str.compare(str2) < 0 && str < str2){ // use compare or directly use < > 
    std::cout << "str comes before str2\n";
  }

  // find returns position where first instance of a substring starts
  // rfind returns position where last instance of a substring starts
  // returns std::string::npos if not found

  // can index strings same way as vector using at (bounds checking) and []
  std::string MyString{"The cat slapped the other cat"s};
  std::cout << "First cat starts at: " << MyString.find("cat") << " - " << MyString[MyString.find("cat")] << "\n"; 
  std::cout << "\nSecond cat starts at: " << MyString.rfind("cat")  << " - " << MyString[MyString.rfind("cat")] << "\n"; 

  if (MyString.find("dog") == std::string::npos) {
    std::cout << "There is no dog in this fight\n";
  }

  // note additional bool funcs: starts_with, ends_with, contains

  std::cout << "First 5 characters of str: " << str.substr(0, 5) << "\n"; // if just one arg, starts from that pos to end

  // convert string to number using std::stoi, std::stof, std::stod
  std::string PI{"3.1415926535"s};
  int PiInt{std::stoi(PI)};
  std::cout << "Pi as integer: " << PiInt << "\n";

  // convert numeric type back to string:
  long double PiDouble{3.1415926535};
  std::string PiStr{std::to_string(PiDouble)};
  std::cout << PiStr << "\n";
}