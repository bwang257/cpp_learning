/*
g++ -std=c++20 stl_filesystem.cpp -o run
*/
#include <iostream>
#include <filesystem>
#include <format>
#include <chrono>
#include <string>
namespace fs = std::filesystem;


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
  std::cout << "Your current path is: " << fs::current_path() << "\n";

  if (argc < 2){
    std::cerr << "Please enter a path: ./exe [path]\n";
    exit(1);
  }
  // directory_entries are objects in our file system - files and directories
  fs::directory_entry my_entry(argv[1]); // more readable if use raw string
  // run methods on our objects
  if (!my_entry.exists()) {
    std::cout << "Your path does not exist.\n";
    exit(1);
  }

  std::cout << "The path exists and ";
  if (my_entry.is_directory()) {
    std::cout << "it is a directory\n";
    if (fs::create_directory(R"(./test)")){ // returns true if successful
      std::cout << "directory test was created!\n";
    } else {
      std::cout << "directory test was not created.\n";
    }
    // can also create nested directories
    fs::create_directories(R"(./test/test1/test2)");

    // error handling
    try {
      fs::create_directories(R"(./test/test1/test2)");
    } catch (fs::filesystem_error e) {
      std::cout << e.code() << '\n';
      std::cout << e.what() << "\n";
    }

    copy_file();

    // copy directory, can add flags, combine them with | bitwise operator
    fs::copy( R"(c:\test)", R"(c:\test2)",
      fs::copy_options::skip_existing |
      fs::copy_options::recursive |
      fs::copy_options::directories_only);


  } else if (my_entry.is_regular_file()) {
    std::cout << "it is a file\n";

    std::cout << "\n=== File Statistics ===\n";
    std::cout << "File size: " << my_entry.file_size() << "bytes\n";

    // type returned actually depends on underlying implementation (C++ 17)
    // C++20 has it return std::chrono::time_point<std::chrono::file_clock>, with alias std::filesystem::file_time_type
    fs::file_time_type last_modified{my_entry.last_write_time()};
  
    std::cout << std::format("Last Modified: {}\n", last_modified);
  }
}

