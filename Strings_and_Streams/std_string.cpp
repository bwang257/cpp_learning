/*
Deeper dive into std::string objects

Compile using:
g++ -std=c++23 std_string.cpp -o run
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main(){
  // std::string_literals creates a std::string directly
  using namespace std::string_literals;
  std::string str{"Hello\0world"s}; 
  std::cout << str << "\n";

  std::string str2{"Hi\0world"}; // iniitalize with c str constructor
  std::cout << str2 << "\n";

  // concatenate using + operator (or append method) 
  str2 += " "; // could have also done str.append(" ");

  std::string str3{"World,Everyone,Friends"};
  str2.append(str3, 6, 8); // starting from pos 6 of str3, append 8 characters
  str2.append(3, '!');
  std::cout << str2 << "\n";

  // append a range, c++23
  std::vector<char> Characters{' ', ':', ')'};
  str2.append_range(Characters);
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


  // inserting content
  std::string greeting{"Greetings  "};
  std::string andr{"Andrew"};
  greeting.insert(10, andr);
  std::cout << greeting << "\n";

  std::vector br_and{'B', 'r', 'i', 'a', 'n', ',', ' '};
  greeting.insert_range(greeting.begin()+10, br_and);
  std::cout << greeting << "\n";

  // erasing content
  // greeting.erase() // erase all chars
  // greeting.erase(5) erase everything execept the first 5 chars
  greeting.erase({}, 17); // erase first 17 chars
  std::cout << greeting << "\n";

  // replacing content
  std::string greeting2{"Hello World!"};
  std::string greeting3{greeting2};
  // Starting from index 6, replace 5 characters, str to insert does not have be same length
  greeting2.replace(6, 5, "other students");
  std::cout << greeting2 << "\n";

  // replace_with_range c++23
  std::vector Chars{'E', 'v', 'e', 'r', 'y', 'o', 'n', 'e'};
  greeting3.replace_with_range(greeting3.begin() + 6, greeting3.begin() + 11, Chars);
  std::cout << greeting3 << "\n";

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

  // able to iterate over string (for const char& c : str)...
  // allows use of strings as ranges
  std::string name{"Brian"};
  std::reverse(name.begin(), name.end());

  std::string my_sentence{"The quick brown fox jumped over the log."};

  std::cout << "The string has " << std::ranges::count(my_sentence, ' ') + 1 << " word\n";


  // std::string is alias for std::basic_string<char>

  // L is literal for creating wide char str
  std::wstring w_str{L"Hello\n"}; // std::basic_string<wchar_t>
  std::wcout << w_str; // need wcout, cout is intended for narrow characters
}
