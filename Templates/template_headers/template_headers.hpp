// Declare class template in header file
// Can define implementations here 

#pragma once
#include <iostream>

// can define implementations in a separate file
// convention states that we provide implementations .ipp or .tpp extensions

template<typename t1, typename t2>
class Pair {
  public:
    Pair(t1 first, t2 second) : first{first}, second{second} {}
    t1 first;
    t2 second;
    t1 get_first() const;
    t2 get_second() const;
};

// ** include the ipp file after the class template definition **

#include "template_headers.ipp"

// Can define implementation here but generally separate
// extra syntax here because class templates can be used to create any number of classes

// template<typename t1, typename t2>
// t1 Pair<t1, t2>::get_first() const {
//   std::cout << "Getting first" << std::endl;
// }

// template<typename t1, typename t2>
// t2 Pair<t1, t2>::getsecond() const {
//   std::cout << "Getting second" << std::endl;
// }







