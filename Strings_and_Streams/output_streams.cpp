/*
Output streams (in the context of std::cout)

g++ output_streams.cpp -o run
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <cassert>

void manipulators(){

  // changing base, setw only applied to next output
  // can also do std::setbase(8/10/16) instead of std::dec/hex/oct
  int val = 255;
  std::cout << std::setw(13) << "Decimal: " << std::dec << val << "\n";
  std::cout << std::setw(13) << "Hexadecimal: " << std::hex << val << "\n"; 
  std::oct(std::cout); // can also use as a func
  std::cout << std::setw(13) << "Octal: " << val << "\n\n";
  std::cout << std::dec;
  // note: using std::cout << std::setfill(char) fills in space from setw with that char

  // printing bools
  bool b1{true};
  bool b2{false};
  std::cout << "  boolalpha: " << std::boolalpha << b1 << " " << b2 << "\n";
  std::cout << "noboolalpha: " << std::noboolalpha << b1 << " " << b2 << "\n\n"; // default

  // setting precision
  float pi{3.141592};
  std::cout << "pi:\n";
  std::cout << std::setprecision(1) << pi << "\n";
  std::cout << std::setprecision(2) << pi << "\n";
  std::cout.precision(3); // use stream method
  std::cout << pi << '\n';
  std::cout << std::setprecision(-1) << pi << "\n\n"; // -1 is default (6 here)

  // ignoring modifiers: put and write methods
  std::cout.put('b'); // single char

  char name[10] = "rian wang";
  std::cout.write(name, 4); // takes in c str and num chars to write
  std::cout << "\n\n";
}

void error_handling(){
  // have recoverable and nonrecoverable errors
  // recoverable: std::ios::failbit is toggled to true
  // unrecoverable: std::ios::badbit true


  // checking these bits 
  // good --> fail and bad bit false
  // fail --> fail or bad bit true
  // bad --> bad bit true
  assert(std::cout.good());

  std::cout.setstate(std::ios::failbit);
  assert(std::cout.fail());

  std::cout.setstate(std::ios::badbit);
  assert(std::cout.bad());
  
  std::cout.clear(); // reverts to good state
  assert(std::cout); // implicit converts to .good()

  // can also throw an exception when either bit is toggled to true
  std::cout.exceptions(std::ios::badbit | std::ios::failbit); 
  
  // not very meaningful output
  try {
    std::cout.setstate(std::ios::badbit);
  } catch (const std::ios::failure& e){
    std::cerr << e.what() << '\n'; 
  }
  std::cout.clear();
  
  try {
    std::cout.setstate(std::ios::failbit);
  } catch (const std::ios::failure& e){
    std::cerr << e.what() << "\n\n";
  }
  std::cout.clear();

}

class Person {
  public:
    Person(std::string name) : name{name}{}
    Person(std::string name, int age) = delete;

    void age_up(int yrs){ age+=yrs; }

    std::string name;
    int age{};
};

std::ostream& operator<<(std::ostream& stream, const Person& person){
  stream << person.name << " (age " << person.age << ")";
  return stream;
}

void custom_types(){
  Person brian{"Brian"};
  std::cout << brian << "\n";
  brian.age_up(20);
  std::cout << brian << "\n\n";
}


int main(){
  std::cout << '\n';
  manipulators();
  error_handling();
  custom_types();

  std::cout << "All assertions passed!\n";
}