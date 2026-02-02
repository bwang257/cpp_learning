/*
Discussion of the mutable keyword
*/

#include <iostream>
#include <string>
#include <exception>

// the const keyword is used for documentation and for compiler checks
// however, if you are returning an unmodified var but modfiy a different var
// you can't mark it as const

// the mutable keyword allows you to modify a var while still marking the class
// member function as const

class cookie {
  public:
    cookie(std::string type, int size) : type{type}, size{size} {}

    int get_size() const {
      num_calls++;
      return size;
    }

    std::string get_type() const {
      num_calls++;
      return type;
    }
  
    std::string type;
    int size;
    mutable int num_calls{0};
};

int main(int argc, char* argv[]){

  int n = 5;
  if (argc > 1){
    try {
      n = std::atoi(argv[1]);
    } catch (const std::exception& e){
      std::cerr << "Error: " << e.what() << "\n";
      exit(1);
    }
  }
  std::cout << "Calling each function " << n << " times.\n";
  cookie gb{"gingerbread", 6};
  int gb_size;
  std::string gb_type;
  for (int i{}; i < n; i++){ gb_size = gb.get_size(); gb_type = gb.get_type(); }
  std::cout << gb.num_calls << "\n";
}
