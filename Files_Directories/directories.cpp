/*
filesystem directory functions used in filesystem.cpp to create interactive program with user
*/

#include "directories.hpp"

// forward declarations:
void check_directory_path();
void create_simple_directory();
void create_nested_directories();
void copy_directory();
void delete_directory();


void directory_work(){
  std::string input;
  std::cout << "Select an Option:\n";
  std::cout << "1: Enter a potential path to a directory\n";
  std::cout << "2: Create a directory\n";
  std::cout << "3: Created nested directories\n";
  std::cout << "4: Copy directories to another directory\n";
  std::cout << "5: Rename a directory\n";
  std::cout << "6: Delete a directory\n";

  std::cout << "\n";

  std::cin >> input;
  int choice{process_input(input)};

  switch(choice) {
    case 1:
      check_directory_path();
      break;
    case 2:
      create_simple_directory();
      break;
    case 3:
      create_nested_directories();
      break;
    case 4: 
      copy_directory();
      break;
    case 5:
      rename_directory();
      break;
    case 6:
      delete_directory();
      break;
    default:
      std::cerr << "Option selected invalid.\n";
  }
}

void check_directory_path(){
  std::string d_path;
  std::cout << "Enter a path: ";
  std::cin >> d_path;
  fs::directory_entry my_directory{d_path};
  if (!my_directory.exists() || !my_directory.is_directory()){
    std::cerr << "Error: Entered path " << d_path << " is not a directory or does not exist\n";
  } else {
    std::cout << "Your path exists and is a directory!\n";

    std::string input2;
    std::cout << "\nWould you like to see storage space associated with the directory? (y/n) \n";
    std::cin >> input2;
    if (input2 == "y"){
      auto [capacity, free, available]{fs::space(d_path)};
      constexpr int bytesInGB{1024*1024*1024};

      std::cout << "\n === Disk Space Info ===\n";
      std::cout << "Capacity: " << capacity / bytesInGB << "GB\n";
      std::cout << "Free: " << free / bytesInGB << "GB\n";
      std::cout << "Available: " << available / bytesInGB << "GB\n";
    }
  }   
}

void create_simple_directory(){
  std::string d_name;
  std::cout << "Enter directory name: ";
  std::cin >> d_name;

  try {
    fs::create_directory(d_name);
    std::cout << "Directory " << d_name << " created successfully.\n";
  } catch (const fs::filesystem_error& e){
    std::cerr << "Error: " << e.what() << "\n";
  }
}

void create_nested_directories(){
  std::string d_names;
  std::cout << "Enter nested directories: ";
  std::cin >> d_names;
  try {
    fs::create_directories(d_names);
    std::cout << "Directories " << d_names << " created successfully\n";
  } catch (const fs::filesystem_error& e){
    std::cerr << "Error: " << e.what() << "\n";
  }
}

void copy_directory(){
  std::string d_path1;
  std::string d_path2;
  std::cout << "Enter directory path to copy: ";
  std::cin >> d_path1;
  std::cout << "Enter directory path to copy to: ";
  std::cin >> d_path2;
  try {
    fs::copy(d_path1, d_path2, fs::copy_options::skip_existing | fs::copy_options::recursive | fs::copy_options::directories_only);
    std::cout << "Directory " << d_path1 << " successfully copied to " << d_path2 << "\n";
  } catch (const fs::filesystem_error& e){
    std::cerr << "Error: " << e.what() << "\n";
  }
} 


void delete_directory(){
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
}

void rename_directory(){
  std::string curr_dir_path;
  std::string new_dir_path;
  std::cout << "Enter directory to rename: ";
  std::cin >> curr_dir_path;
  std::cout << "Enter new path/dir name: ";
  std::cin >> new_dir_path;
  try {
    fs::rename(curr_dir_path, new_dir_path);
    std::cout << "Directory " << curr_dir_path << " successfully renamed to " << new_dir_path << "\n";
  } catch (const fs::filesystem_error& e){
    std::cerr << "Error: " << e.what() << "\n";
  }
}