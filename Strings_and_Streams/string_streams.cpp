/*
String Streams in C++

g++ string_streams.cpp -o run
*/

// concatenating strings can lead to temporary strings 
// --> string streams handle mdemory more efficiently

#include <iostream>
#include <sstream>
#include <cassert>


void ostringstream(){
  // output stream, uses tellp and seekp
  std::ostringstream stream;
  stream << "Hel" << "lo";
  std::cout << stream.str() << '\n';

  // concantentation occurs at an internal position
  std::cout << "\nOutput position: " << stream.tellp() << '\n';

  // initializing a ostringstream place this pos at 0
  std::ostringstream stream2{"Hello"};
  assert(stream2.tellp() == 0); 

  // adding overrides existing chars:
  stream2 << "hE";
  std::cout << stream2.str() << '\n';

  // seekp allows us to either go to a absolute pos or relative pos
  stream.seekp(3);
  assert(stream.tellp() == 3); 

  stream.seekp(-2, std::ios::cur); // std::ios::beg/cur/end
  assert(stream.tellp() == 1);

  // .str(string) replaces contents, internal pos set to 0
  stream.str("New String");
  assert(stream.tellp() == 0);

  // stream behavior has many options, typically called open modes
  // std::ios::ate "at the end" --> atuomatically seeks to the end upon construction and
  // when we reset using .str("string").
  // default for ostringstream is ios::out

  std::ostringstream stream3{"Hi there", std::ios::out | std::ios::ate};
  assert(stream3.tellp() == 8);
  stream3.str("Hello");
  assert(stream3.tellp() == 5);
  stream3.seekp(-2, std::ios::end);
  assert(stream3.tellp() == 3);

  std::cout << '\n';
}



int main(){
  ostringstream();

  std::cout << "All assertions passed.\n";

}