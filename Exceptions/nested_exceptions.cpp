/*
Introduction to nested exceptions
*/

#include <iostream>

// create nested exceptions using std::throw_with_nested
void GenerateExceptions() {
  try {
    throw std::runtime_error{"Error One"};
  } catch (...) {
    try {
      std::throw_with_nested(std::runtime_error{"Error Two"});
    } catch (...) {
      try {
        std::throw_with_nested(std::runtime_error{"Error Three"});
      // catch outer exception
      } catch (const std::exception& e) {
        // check nested
        auto NestedException{dynamic_cast<const std::nested_exception*>(&e)};
        if (NestedException){
          std::cout << "There's a nested exception here\n";
        }
        // rethow_if_nested 
        // std::rethrow_if_nested(e);
        throw;
      }
    }
  }
}


// handle exceptions recursively
void HandleExceptions(const std::exception& e) {
  std::cout << "\nHandling " << e.what();
  try {
    std::rethrow_if_nested(e);
    std::cout << std::endl;
  } catch (const std::exception& Nested) {
    HandleExceptions(Nested);
  }
}

int main(){
  try {
    GenerateExceptions();
  } catch (std::exception& e){
    HandleExceptions(e);
  }
}