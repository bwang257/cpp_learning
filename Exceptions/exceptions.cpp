/*
Introduction to throw, try, and catch and exceptions

 */

// be aware of unreachable code when an exception is thrown
// execution of a throw is like a return, except a function exits without returning normally
// this can lead to memory leaks --> use smart pointers or try catch blocks

#include <iostream>
#include <string>
#include <stdexcept> // standard library exceptions

void basicThrow(){
    // can also throw other data types (bool, int, etc.)
    throw "some error";
    std::cout << "This is unreachable code\n";
}

int divide(int x, int y){
  if (y==0){
    throw std::invalid_argument {"Cannot divide by 0"};
  }
  return x/y;
}

// custom exception types
class AuthenticationError : public std::exception {
  public:
    AuthenticationError(std::string email, std::string password) : Email{email}, Password{password} {}
    
    const char* what() const noexcept override {
      // member function of std::string, returns a read only ptr 
      return m_errorMessage.c_str();
    }

    std::string Email;
    std::string Password;
    std::string m_errorMessage{"Failed to log in"};
};

void tryLogin(std::string email, std::string password){
  throw AuthenticationError{email, password};
}


int main(){
  try {
    basicThrow();
  } catch (const char* e) { // catch string exceptions
    // don't need to add e variable
    std::cout << "Caught an error in catch(const char*): " << e << std::endl;
    
  } catch (...) {
    std::cout << "Caught an error in catch all statement catch(...)\n";
  }
  std::cout << "The program continuing: recovered sucessfully\n";

  // custom messages with base std::exception
  try {
    divide(4, 0);
  } catch (const std::invalid_argument& e){ // convention to catch by reference, const if preferred
    // if we catch by reference and the exception is part of a more specific class, we lose that
    // class's unique variables/data --> object slicing
    std::cout << "Invalid argument: " << e.what() << std::endl;
  }
  try {
    divide(4, 0);
  } catch (const std::exception e){
    std::cout << "Invalid argument: " << e.what() << std::endl;
  }

  // if multiple catch statements, first valid one for the thrown exception is used
  try {
    throw std::logic_error("Oops!");
  } catch (std::logic_error& e) {
    std::cout << "Logic Error: " << e.what() << "\n";
  } catch (std::exception& e) {
    std::cout << "Exception:" << e.what() << "\n";
  }

  // using custom exception
  try {
    tryLogin("myemail@gmail.com", "123");
  } catch (AuthenticationError& e){
    std::cout
      << "\nAuthenticationError Handler:\n"
      << e.what() << "\nEmail: " << e.Email << "\nPassword: " << e.Password << std::endl;
  }

  return 0;
}