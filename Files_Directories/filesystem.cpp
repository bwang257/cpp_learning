/*
Exploration of std::file_system through a command line interface

Compile with:
g++ -std=c++23 filesystem.cpp directories.cpp files.cpp utility.cpp -o run
*/

#include "directories.hpp"
#include "files.hpp"


void path_work(){
  std::string y_n;
  std::cout << "Use current path? (y/n)\n";
  std::cin >> y_n;
  fs::path curr_loc;
  if (y_n == "n"){
    std::string user_path;
    std::cout << "Enter path: ";
    std::cin >> user_path;
    curr_loc = user_path;
    fs::directory_entry path_loc{curr_loc};
    if (!path_loc.exists()){
      std::cerr << "Entered path does not exist\n";
      return;
    }
  } else { curr_loc = fs::current_path(); }

  std::cout << "Your current path is: " << curr_loc.string() << "\n";
  do {
    std::cout << "\nWould you like to add anything to this path? (y/n)\n";
    std::cin >> y_n;
    if (y_n == "y"){
      std::string input;
      std::cout << "Enter what to append: ";
      std::cin >> input;
      curr_loc /= input;
      std::cout << "Current path: " << curr_loc.string() << "\n";
      fs::directory_entry test_loc{curr_loc};
      if (!test_loc.exists()){
        std::cerr << "Entered path does not exist!\n";
        return;
      }
    }
  } while (y_n == "y");

  std::cout << "\n";

  if (curr_loc.is_absolute()){ std::cout << "Current path is absolute.\n"; }
  if (curr_loc.is_relative()){ std::cout << "Current path is relative.\n"; }

  if (curr_loc.has_filename()) { std::cout << "File name: " << curr_loc.filename().string() << "\n"; }
  if (curr_loc.has_stem()) { std::cout << "File Stem: " << curr_loc.stem().string() << "\n"; }
  if (curr_loc.has_extension()){ std::cout << "File extension: " << curr_loc.extension().string() << "\n"; }
  if (curr_loc.has_parent_path()) { std::cout << "Parent path: " << curr_loc.parent_path().string() << "\n"; }
  if (curr_loc.has_root_name()) { std::cout << "Root path: " << curr_loc.root_name().string() << "\n"; }

  // can then manipulate file
  if (curr_loc.has_extension()){
    std::cout << "Create backup? (y/n)\n";
    std::cin >> y_n;
    if (y_n == "y"){
      fs::path backup{curr_loc};
      backup.replace_extension("backup");
      fs::copy_file(curr_loc, backup);
    }
  }
}


int main(int argc, char* argv[]){
  std::string input;
  bool continueLoop{true};
  while (continueLoop){
    std::cout << "Choose an Option:\n";
    std::cout << "1: Work with paths\n";
    std::cout << "2: Work with directories\n";
    std::cout << "3: Work with files\n";
    std::cout << "4: quit\n";

    std::cout << "\n";
    std::cin >> input;

    int choice{process_input(input)};

    switch (choice){
      case 1:
        path_work();
        break;
      case 2:
        directory_work();
        break;
      case 3:
        file_work();
        break;
      case 4:
        continueLoop = false;
        break;
      default:
        std::cout << "Option selected invalid.\n";
    }
    std::cout << "\n";
  }
}

