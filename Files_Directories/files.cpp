/*
filesystem file functions used in filesystem.cpp to create interactive program with user
*/

#include "files.hpp"

// forward declarations:
void check_file_path();
void copy_file();
void delete_file();

void file_work(){
  std::string input;
  std::cout << "Select an Option:\n";
  std::cout << "1. Enter a potential path to a file\n";
  std::cout << "2. Copy a regular file\n";
  std::cout << "3. Delete a file\n";
  std::cout << "\n";
  std::cin >> input;

  int choice{process_input(input)};

  switch(choice){
    case 1:
      check_file_path();
      break;
    case 2:
      copy_file();
      break;
    case 3:
      delete_file();
      break;
    default:
      std::cout << "Invalid option selected.\n";
  }
}


void check_file_path(){
  std::string f_path;
  std::cout << "Enter path: ";
  std::cin >> f_path;
  fs::directory_entry my_file{f_path};
  if (!my_file.exists() || !my_file.is_regular_file()){
    std::cerr << "Error: Entered path " << f_path << " is not a file or does not exist\n";
  } else {
    std::cout << "Your path exists and is a regular file!\n";
    std::string input2;
    std::cout << "Would you like too print file statistics? (y,n)\n";
    std::cin >> input2;
    if (input2 == "y"){
      std::cout << "\n=== File Statistics ===\n";
      std::cout << "File size: " << my_file.file_size() << "bytes\n";

      // type returned actually depends on underlying implementation (C++ 17)
      // C++20 has it return std::chrono::time_point<std::chrono::file_clock>, with alias std::filesystem::file_time_type
      fs::file_time_type last_modified{my_file.last_write_time()};
      std::cout << std::format("Last Modified: {}\n", last_modified);
    }
  }
}

void copy_file(){
  try {
    // copy_files, first arg is file to copy, second arg is to where
    std::string input_path1;
    std::string input_path2;
    std::cout << "Enter a path to a file to copy: ";
    std::cin >> input_path1;
    std::cout << "Enter a path to copy the file to: ";
    std::cin >> input_path2;

    // skip_existing: if file exists, dont overwrite, don't throw exception
    fs::copy_file(input_path1, input_path2, fs::copy_options::skip_existing);

  } catch (const fs::filesystem_error e){
    std::cout << e.what() << "\n";
    exit(1);
  }
}


void delete_file(){
  std::string f_delete;
  std::string delete_yn;
  std::cout << "Enter a file to delete: ";
  std::cin >> f_delete;
  std::cout << "Are you sure you want to delete " << f_delete << " (y,n)?\n";
  std::cin >> delete_yn;
  if (delete_yn == "y"){
    try {
      fs::remove(f_delete);
      std::cout << f_delete << " has been deleted successfully\n";
    } catch (const fs::filesystem_error& e){
      std::cerr << "Error: " << e.what() << '\n';
    }
  }
}