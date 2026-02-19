// .ipp file that defines implemntations for the class template defined 
// in template_headers.hpp

#pragma once
#include "template_headers.hpp"

template<typename t1, typename t2>
t1 Pair<t1, t2>::get_first() const {
  std::cout << "Getting first" << std::endl;
  return first;
}

template<typename t1, typename t2>
t2 Pair<t1, t2>::get_second() const {
  std::cout << "Getting second" << std::endl;
  return second;
}