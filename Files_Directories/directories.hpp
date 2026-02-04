/*
Header file for filesystem directory functions used in filesystem.cpp
*/

#pragma once
#include <iostream>
#include <filesystem>
#include <format>
#include <chrono>
#include <string>
#include <system_error>
#include <stdexcept>
#include "utility.hpp"

namespace fs = std::filesystem;

void check_directory_path();
void create_simple_directory();
void create_nested_directories();
void copy_directory();
void delete_directory();
void directory_work();