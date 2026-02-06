/*
Header file for filesystem file functions used in filesystem.cpp
*/

#pragma once
#include <iostream>
#include <filesystem>
#include <format>
#include <chrono>
#include <string>
#include <system_error>
#include <stdexcept>
#include <fstream>
#include <limits>
#include <cstdio>
#include "utility.hpp"

namespace fs = std::filesystem;

void file_work();
void create_file();
void check_file_path();
void copy_file();
void delete_file();
void rename_file();