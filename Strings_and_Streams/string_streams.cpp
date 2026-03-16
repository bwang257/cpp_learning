/*
String Streams in C++

g++ string_streams.cpp -o run
*/

#include <iostream>
#include <sstream>
#include <string>
#include <cassert>

class Stock{
  public:
    // simple example of how data in a stream can used to create objections
    Stock(std::istringstream& stream){
      stream >> ticker;
      stream >> exchange; 
      std::string temp;
      while (stream >> temp){
        name += temp + " ";
      }
    }

    std::string ticker;
    std::string exchange;
    std::string name{""};
};

// concatenating strings can lead to temporary strings 
// --> string streams handle memory more efficiently
void ostringstream(){
  // output stream, uses tellp and seekp
  std::ostringstream stream;
  stream << "Hel" << "lo";
  std::cout << '\n' << stream.str() << '\n';

  // concantentation occurs at an internal position
  std::cout << "Output position: " << stream.tellp() << '\n';

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

void istringstream(){
  // input stream, uses tellg, seekg
  // default delimited is space, need std::getline for other types
  std::istringstream stream{"Hello World"};
  std::string s1, s2;
  

  // have internal collections of flags --> eof bit, failbit (stream not compromised), badbit (state might not be expected)
  assert(stream.good() && stream); // no bits set, equivalent expressions

  stream >> s1 >> s2;
  assert(s1 == "Hello" && s2 == "World");

  assert(stream.eof()); // eofbit set
  stream >> s1;
  assert(stream.fail()); // fail or badbit set
  assert(!stream.bad()); // badbit set

  // since istringstream converts into .good() bool and >> returns istringstream:
  // tellg is the curr pos, -1 when at end (or very uncommon, when the underlying stream doesnt support tellp)
  std::istringstream stream2{"a b c d e f g"};
  unsigned int cnt{};
  std::cout << "tellg: ";
  while (stream2 >> s2){
    ++cnt;
    std::cout << stream2.tellg() << ", ";
  }
  std::cout << '\n';

  assert(cnt == 7);

  // seekg used similar to seekp
  std::istringstream stream3{"Wang Brian"};
  stream3.seekg(4);
  stream3 >> s2;
  stream3.seekg(0, std::ios::beg);
  stream3 >> s1;
  std::cout << s2 << " " << s1 << '\n';

  // std::getline, returns reference to input stream so we can use in while loop
  // default delimter is \n
  std::istringstream stream4{"This,is,a,csv,file"};
  std::string input;
  cnt = 0;
  while(std::getline(stream4, input, ',')){ // 3rd arg optional
    ++cnt; 
  }
  assert(cnt == 5);

  // get gets a single char returns reference to stream
  std::istringstream stream5{"124"};
  cnt = 0;
  char extract;
  while(stream5.get(extract)){
    ++cnt;
  }
  assert(cnt == 3);

  // can also add size of chars to get, write to a char*, space reserved for null terminator
  std::istringstream stream6{"1234567,89"};
  char c_str[5];
  stream6.get(c_str, sizeof(c_str)); // 5th char saved for null terminator
  std::cout << c_str << '\n';

  // can also use with delimiters, not moved past delimeter
  char c_str2[100];
  std::string remainder;
  stream6.get(c_str2, sizeof(c_str2), ',');
  stream6 >> remainder;
  std::cout << c_str2 << " | " << remainder << '\n'; // remainder includes delimiter

  // peek used to check next char but input pos not moved
  // since compiler doesn't know what data in stream, it can interpret as a number
  std::istringstream stream7{"Hello\nWorld\n"};
  std::cout << "Next value: " << stream7.peek() << "\n"; // 72 --> ASCII for 'H'
  std::cout << "Next char:  " << static_cast<char>(stream7.peek()) << '\n';

  // good for when std::getline stops at delimiter and doest not check if eof has been reached
  std::getline(stream7, s1);
  std::getline(stream7, s1);
  assert(!stream7.eof());
  stream7.peek();
  assert(stream7.eof());

  // example creating object
  std::istringstream data{"AMZN NASDAQ Amazon.com Inc."};
  Stock amzn{data};
  std::cout << amzn.ticker << " (" << amzn.exchange << "): " << amzn.name << "\n\n";
}

int main(){
  ostringstream();
  istringstream();

  std::cout << "All assertions passed.\n";
}