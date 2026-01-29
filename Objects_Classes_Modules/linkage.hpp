/*
Header file to supplement exploration of linkage
*/

#pragma once

// if #include "linkage.hpp" was included in both cpp files, 
// then you would have two definitions of Global, even if we use
// pragma once. The c++17 solution is to use inline keyword, such that
// only one object file maintains the definition of Global

inline int Global{42};