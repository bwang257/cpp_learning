/*
Regular Expressions

g++ regex.cpp -o run
*/

#include <iostream>
#include <string>
#include <regex>

  /*
  .         --> wildcard, can stand for a single chracter
  cat|hat   --> match to either cat or hat
  a?        --> a is optional
  ^hat      --> hat is at beginning of input
  hat$      --> hat is at end of input
  [ch]at    --> (c or h) + at
  [^cbm]at  --> can't be cat, bat, mat, negated
  cat[.]    --> . taken literally. Same applies to ?, ^, *
  [0-9]d    --> 0d, 1d, ... 9d
  [0-9a-z]d --> [0-9]d and ad, bd, ... work
  \d        --> shortcut for [0-9]
  \w        --> shortcut for any alphabetic character, digit, or underscore, equivalent to [a-zA-Z0-9_]
  \s        --> shortcut for any whitespace
  \\w       --> literal \w
  a*c       --> 0 or more char between a and c
  a+c       --> 1 or morechar between a and c
  a{2}c     --> exactly two repetitions of a, then c
  a{2,}c    --> at least two repetitions of a, then c
  a{2,5}c   --> 2 to 5 repetitions of a, then c
  a.{2}c    --> exactly 2 of any char between and c
  c\w*t     --> any amt of letters, digit, or undersore between c and t
  */

void special_characters(){

  // example of an application
  using namespace std::string_literals;

  // construct pattern using string literal
  // wrap in ^ and $ to make exact match
  std::regex pattern{R"(^b\w*[abc]{1,3}\s\d+$)"};
  std::string input{"b4klnv42b4936cfsndkbc 1234"s};
  bool match{std::regex_match(input, pattern)};
  if (match) std::cout << "Input and custom mattern match!\n";

  std::cout << "\n";
}


void general_matching(){
  std::string input{"Hello world"};
  std::regex sensitivePattern{"hello"};
  std::regex insensitivePattern{"hello", std::regex::icase}; // case insensitive regex

  // only true if entires str matches
  bool matchResult{std::regex_match(input, insensitivePattern)};
  std::cout  << "The regex_match pattern " << (matchResult ? "did" : "did not") << " match\n";

  bool sensitiveSearch{std::regex_search(input, sensitivePattern)};
  bool insensitiveSearch{std::regex_search(input, insensitivePattern)};

  std::cout  << "The regex_search pattern sensitive " << (sensitiveSearch ? "did" : "did not") << " match\n";
  std::cout  << "The regex_search pattern sensitive " << (insensitiveSearch ? "did" : "did not") << " match\n";

  std::cout << "\n";
}


int main(){
  general_matching();
  special_characters();
}