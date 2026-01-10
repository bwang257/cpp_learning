/*
Overview of Iterators
*/


// allow any type of container to be compatible with our algorithms, adds to functionality


#include <iostream>
#include <array>
#include <forward_list>
#include <list>
#include <vector>
#include <iterator>

#include <cassert>

void myPrintFunction(int x){
  std::cout << "Curr val: " << x << "\n";
}

// with concepts, need tpyename to specify iterator is not 
// member of any other static member
template <typename T>
void RandAccessAlgorithm(T& container){
  static_assert(std::random_access_iterator<typename T::iterator>, "Only supports random access containers");
  std::cout << "Calling algorithm using random access iterator\n";
}

// with requires
template <typename T>
requires std::forward_iterator<typename T::iterator>
void ForwardAccessAlgorithm(T& container){
  std::cout << "Calling algorithm using forward access iterator\n";
}

// custom concept, check if at least forward but not random access (need to check both)

template <typename T>
concept NotRandomAccess = requires(T) {
  requires std::forward_iterator<typename T::iterator>;
  requires (!std::random_access_iterator<typename T::iterator>);
};


int main(){
  std::array<int, 7> arr{1,2,3,4,5,6,7};

  // iterator to start of the collection
  auto arr_start{arr.begin()};
  std::cout << "\nSize of array with 7 elements: " << sizeof(arr) << " bytes" << "\n";
  std::cout << "Size of array iterator: " << sizeof(arr_start) << " bytes" << "\n";
  std::cout << "Second element: " << *(arr_start+1) << "\n";


  // types of iterators
  // forward iterator (--> 1)
  std::forward_list fl{1,2,3,4,5,6,7};
  std::cout << "\nSize of forward list with 7 elements: " << sizeof(fl) << " bytes" << "\n";
  std::forward_list<int>::iterator forward_start{fl.begin()};
  std::cout << "Size of forward list iterator: " << sizeof(forward_start) << " bytes" << "\n";
  std::cout << "Second element: " << *(++forward_start) << "\n";
  std::cout << "Fourth element: " << *std::next(forward_start, 2) << "\n"; // needs to call ++ twice, two copies, O(n)
  std::cout << "First element: " << *std::prev(forward_start, 3) << "\n"; // same idea with prev

  // bidirectional iterator (-1 <--> 1)
  std::list ll{1, 2, 3, 4, 5, 6, 7}; // double linked list
  std::list<int>::iterator ll_start {ll.begin()};
  std::cout << "\nSize of double linked list with 7 elements: " << sizeof(ll) << " bytes" << "\n";
  std::cout << "Size of double linked list iterator: " << sizeof(ll_start) << " bytes" << "\n";
  std::cout << "Second element: " << *(++ll_start) << "\n";
  std::cout << "First element: " << *(--ll_start) << "\n";
  std::cout << "Last element: " << *std::next(ll.end(), -1) << "\n"; // .end() returns iterator past end


  // random access iterator (any <--> any)
  std::vector vec{1, 2, 3, 4, 5, 6, 7};
  std::vector<int>::iterator vec_start{vec.begin()};
  std::cout << "\nSize of vector with 7 elements: " << sizeof(vec) << " bytes" << "\n";
  std::cout << "Size of vector iterator: " << sizeof(vec_start) << " bytes"  << "\n";
  std::cout << "Seventh element: " << *(vec_start+6) << "\n";
  std::cout << "Second element: " << *(vec_start-5) << "\n";
  std::cout << "Fourth element: " << *std::next(vec_start, 2) << "\n"; // needs to call +=2 once to create copy, O(1)
  std::cout << "First element: " << *std::prev(vec_start, 3) << "\n"; // same idea with prev
  // distance method
  ptrdiff_t dist{vec.end() - vec.begin()};
  std::cout << "Distance between begin and end iterators: " << dist << "\n";
  // or 
  ptrdiff_t dist2{std::distance(vec.begin(), vec.end())}; // similar to next/prev, O(1) for random access iterator, O(n) for forward list iterator (needs to follow path)
  assert(dist2 == dist);

  // std lib for_each algorithm  --> many more
  // pass in iterators, std::for_each dereferences those iterators internally
  // pass starting and ending iterators, and function to call
  std::vector vec2{5, 3, 2, 7, 42};
  std::cout << "\nFor each algorithm\n";
  std::for_each(vec2.begin()+2, vec2.end(), myPrintFunction);
  // objects can be modified through their iterators --> we can use const iterators if needed
  std::for_each(vec2.cbegin(), vec2.cbegin()+2, myPrintFunction); // use cbegin() and cend() for const interators
  
  // reverse iterators using rebegin and rend
  std::vector vec3{100, 101, 102, 103, 104, 105};
  std::for_each(vec3.rbegin(), vec3.rend(), myPrintFunction); // note existence of crbegin() and crend()

  // iterator invalidation --> if we save copy of begin operator and then 
  // move the container, leading to undefined vehavior if we try dereference the iterator

  // just note the exact types for each iterator that exist
  std::vector<int>::iterator A;
  decltype(vec3)::const_iterator B;

  // with concepts
  if constexpr(std::forward_iterator<decltype(forward_start)>){
    std::cout << "var forward_start is a forward iterator";
  }
  if constexpr(!std::random_access_iterator<decltype(forward_start)>){
    std::cout << " but not random access\n";
  }

  RandAccessAlgorithm(vec);
  ForwardAccessAlgorithm(fl);

}


