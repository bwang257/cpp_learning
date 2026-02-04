/*
Exploration of std::file_system through an interactive user interface

Compile with:
g++ -std=c++20 filesystem.cpp directories.cpp files.cpp utility.cpp -o run
*/

#include "directories.hpp"
#include "files.hpp"

int main(int argc, char* argv[]){
  std::string input;
  bool continueLoop{true};
  while (continueLoop){
    std::cout << "Choose an Option:\n";
    std::cout << "1: Print current path\n";
    std::cout << "2: Work with directories\n";
    std::cout << "3: Work with files\n";
    std::cout << "4: quit\n";

    std::cout << "\n";
    std::cin >> input;

    int choice{process_input(input)};

    switch (choice){
      case 1:
        std::cout << "Your current path is: " << fs::current_path() << "\n";
      case 2:
        directory_work();
      case 3:
        file_work();
      case 4:
        continueLoop = false;
        break;
      default:
        std::cout << "Option selected invalid.\n";
    }
    std::cout << "\n";
  }
}

