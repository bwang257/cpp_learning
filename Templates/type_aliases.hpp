// define aliases in a header file that gets included
// in every other file in a project for project wide aliases

#pragma once
#include <cstdint>


// able to change definitions at compile time with help from the preprocessor
// For 64 bits: g++ -DUSE_64_BIT_INTS type_aliases.cpp -o runProgram
#ifdef USE_64_BIT_INTS
  using Integer = int64_t;
#else
  // 32 bits/ 4 byte memory integers
  using Integer = int32_t;
#endif

