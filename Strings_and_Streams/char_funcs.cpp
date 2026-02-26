/*
functions to use on chars in c++, useful for Leetcode right now
- cctype library
*/

/*
I static cast characters to unsigned char, which is good for safety and portability
but for general ASCII characters (0-127), this cast doesn't change their value

Note that A-Z range from 65 - 90, a-z 97-122

ex. ASCII vals > 127 cast to negative numbers that aren't handled by lib functions
*/

#include <iostream>
#include <string>
#include <cctype>


void check_properties(){
  std::string input{"5nsd?dSh5jk\t44s234.nSg  shAGs73!4fd\t\tgDDS?FDE"};
  int num_alnum{0};
  int num_letters{0};
  int num_spaces{0};
  int num_numbers{0};
  int num_upper{0};
  int num_lower{0};
  int num_punct{0};
  
  for (const char& c : input){
    char uc = static_cast<unsigned char>(c);
    if (std::isalnum(uc)) num_alnum+=1;
    if (std::isalpha(uc)) num_letters+=1;
    if (std::isblank(uc)) num_spaces+=1; // includes ' ' and '\t'
    if (std::isupper(uc)) num_upper+=1;
    if (std::islower(uc)) num_lower+=1;
    if (std::ispunct(uc)) num_punct+=1;
    if (std::isdigit(uc)) num_numbers+=1;
  }

  std::cout << "String: " << input << "\n";
  std::cout << "The strin has " << num_alnum << "letters and numbers\n";
  std::cout << "The string has " << num_letters << " letters and " << num_numbers << " numbers\n";
  std::cout << "The string has " << num_upper << " uppercase letters and " << num_lower << " lowercase letters\n";
  std::cout << "There were also " << num_spaces << " whitespaces and " << num_punct << " punctuation marks\n";
  std::cout << "\n";
}

void modify_chars(){
  std::string init{"AbCdEfGhIjKlMnOpQrStUvWxYz"};
  std::string final{""};
  for (const char& c : init){
    if (std::isupper(c)) final+=std::tolower(c);
    else final+= std::toupper(c);
  }

  std::cout << "Initial string: " << init << "\n";
  std::cout << "Final string:   " << final << "\n";
  std::cout << "\n";
}


int main(){
  check_properties();
  modify_chars();
}