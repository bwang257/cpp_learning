/*
g++ -std=c++20 stl_filesystem.cpp -o run
*/
#include <iostream>
#include <filesystem>
#include <format>
#include <chrono>
#include <string>
#include <system_error>
namespace fs = std::filesystem;

void copy_file();

void directory_work(){
  std::string input;
  std::cout << "Select an Option:\n";
  std::cout << "1. Enter a potential path to a directory\n";
  std::cout << "2. Create a directory\n";
  std::cout << "3. Created nested directories\n";
  std::cout << "4. Copy directories to another directory\n";
  std::cout << "5. Delete an empty directory\n";
  std::cout << "6. Delete a directory\n";
  std::cout << "\n";

  std::cin >> input;

  if (input == "1"){
    std::string d_path;
    std::cout << "Enter a path: ";
    std::cin >> d_path;
    fs::directory_entry my_directory{d_path};
    if (!my_directory.exists() || !my_directory.is_directory()){
      std::cerr << "Error: Entered path " << input << " is not a directory or does not exist\n";
    } else {
      std::cout << "Your path exists and is a directory!\n";
    }   
  } else if (input == "2"){
    std::string d_name;
    std::cout << "Enter directory name: ";
    std::cin >> d_name;

    try {
      fs::create_directory(d_name);
      std::cout << "Directory " << d_name << " created successfully.\n";
    } catch (const fs::filesystem_error& e){
      std::cerr << "Error: " << e.what() << "\n";
    }
  } else if (input == "3"){
    std::string d_names;
    std::cout << "Enter nested directories: ";
    std::cin >> d_names;
    try {
      fs::create_directories(d_names);
      std::cout << "Directories " << d_names << " created successfully\n";
    } catch (const fs::filesystem_error& e){
      std::cerr << "Error: " << e.what() << "\n";
    }
  } else if (input == "4"){
    std::string d_path1;
    std::string d_path2;
    std::cout << "Enter directory path to copy: ";
    std::cin >> d_path1;
    std::cout << "Enter directory path to copy to: ";
    std::cin >> d_path2;
    fs::copy(d_path1, d_path2,
      fs::copy_options::skip_existing | 
      fs::copy_options::recursive | 
      fs::copy_options::directories_only); // apply | bitwise operator

  } else if (input == "5"){
    std::string d_delete;
    std::cout << "Enter a directory to delete: ";
    std::cin >> d_delete;

    try {
      fs::remove(d_delete);
      std::cout << "Directory " << d_delete << " deleted.\n";
    } catch (const fs::filesystem_error& e){
      if (e.code() == std::errc::directory_not_empty){
        std::string delete_yn;
        std::cout << d_delete << " is not empty. Delete anyway? (y/n)\n";
        std::cin >> delete_yn;
        if (delete_yn == "y"){
          try {
            uintmax_t files_deleted{fs::remove_all(d_delete)};
            std::cout << "Successfully deleted " << files_deleted << " files or directories.\n";
          } catch (const fs::filesystem_error& e){
            std::cerr << "Error: " << e.what() << "\n";
          }
        }  
      } else {
        std::cout << e.code() << "\n";
        std::cerr << "Error: " << e.what() << "\n";
      }
    }
  } else if (input == "6"){
    std::string d_delete;
    std::string delete_yn;
    std::cout << "Enter a directory to delete: ";
    std::cin >> d_delete;
    std::cout << "Are you sure? Directory to delete: " << d_delete << " (y/n)\n";
    std::cin >> delete_yn;
    if (delete_yn == "y"){
      try {
        uintmax_t files_deleted{fs::remove_all(d_delete)};
        std::cout << "Successfully deleted " << files_deleted << " files or directories.\n";
      } catch (const fs::filesystem_error& e){
        std::cerr << "Error: " << e.what() << "\n";
      }
    }
  }
}


void file_work(){
  std::string input;
  std::cout << "Select an Option:\n";
  std::cout << "1. Enter a potential path to a file\n";
  std::cout << "2. Copy a regular file\n";
  std::cout << "3. Delete a file\n";
  std::cout << "\n";
  std::cin >> input;


  if (input == "1"){
    std::string f_path;
    std::cout << "Enter path: ";
    std::cin >> f_path;
    fs::directory_entry my_file{f_path};
    if (!my_file.exists() || !my_file.is_regular_file()){
      std::cerr << "Error: Entered path " << input << " is not a file or does not exist\n";
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
  } else if (input == "2"){
    copy_file();
  } else if (input == "3"){
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


int main(int argc, char* argv[]){
  std::string input{""};
  while (true){
    std::cout << "Choose an Option:\n";
    std::cout << "p: Print current path\n";
    std::cout << "d: Work with directories\n";
    std::cout << "f: Work with files\n";
    std::cout << "q: quit\n";

    std::cout << "\nInput: ";
    std::cin >> input;

    if (input == "q"){
      break;
    } else if (input == "p"){
      std::cout << "Your current path is: " << fs::current_path() << "\n";
    } else if (input == "d"){
      directory_work();
    } else if (input == "f"){
      file_work();
    }

    std::cout << "\n";
  }
}

