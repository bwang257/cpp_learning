/*
Introduction to storing and rethrowing exceptions
*/

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>


class AuthenticationError : public std::exception {
 public:
  AuthenticationError(std::string Password) : Password(Password) {}
  const char* what() const noexcept override {
    return "A user failed to log in";
  };
  std::string Password;
};

void Auth(std::string Password) {
  throw AuthenticationError{Password};
}

// exception ptr can point to any type of object that was thrown
// can be nullptr
void HandleException(std::exception_ptr e){
  if (e){
    std::cout << "An exception was handled";
    try {
      // rethrow back to the stack
      std::rethrow_exception(e); // can rethrow using std::exception_ptr
    } catch (...) {
      std::cout << " even after being rethrown\n";
    }
  }
}


void Login(std::string Password) {
  try {
    Auth(Password);
  } catch (AuthenticationError& e) {
    // conditional rethrow
    if (Password.empty()){
      std::cout << "Handled by Login(): ";
      HandleException(std::current_exception()); // captures currently handles exception or nullptr
    } else {
      // Rethrow exception using throw in the catch block 
      // to be handled elsewhere in the stack
      std::cout << "Security Alert - Login Fail: " << e.Password << '\n';
      throw; // we don't do throw e because we shouldnt copy the expception
      // and there may be slicing (data loss) where the copied exception is in the base type
    }
  }
}

int main(){
  try {
    Login("wrong_password");
  } catch (std::exception& e){
    std::cout << "Handled by main\n";
  }
  try {
    Login("");
    std::cout << "This runs fine\n";
  } catch (std::exception& e){
    std::cout << "Handled by main\n";
  }
}