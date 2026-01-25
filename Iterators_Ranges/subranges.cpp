/*
Creating views using std::ranges::subrange
*/

#include <iostream>
#include <vector>
#include <ranges>
#include <forward_list>


// takes in the type of iterator
void add_one(int& val){
    val+=1;
}
void log_num(const int& val){
  std::cout << val << ", ";
}

int main(){

  // using std::ranges::subrange to create a view
  std::vector myNums{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::ranges::subrange FullView{myNums};
  std::ranges::subrange SubView{myNums.begin()+1, myNums.end()-1};

  // subranges are a view, they are nonowning
  std::cout << "Nums complete: ";
  for (const auto& val : FullView){
    std::cout << val << ", ";
  }
  std::cout << "\nSubview: ";

  for (const auto& val : SubView){
    std::cout << val << ", ";
  }
  std::cout << "\n";

  // modifiying a subrange modifies the original container
  std::ranges::for_each(FullView, add_one);
  std::cout << "new vector after view was modified: ";
  std::ranges::for_each(myNums, log_num);
  std::cout << "\n";

  // ** size method only works if can be found in constant time. **
  // forward list doesn't work because of this
  // we can check if the range meets the requirements using std::ranges::sized_range<T>
  if constexpr(std::ranges::sized_range<decltype(FullView)>){
    std::cout << "That range is of size: " << FullView.size() << "\n";
  } else {
    std::cout << "The size of the range cannot be found using .size()\n";
  }

  std::forward_list myNums2{1, 2, 3, 4, 5};
  if constexpr(!std::ranges::sized_range<decltype(myNums2)>){
    std::cout << "Forward lists do not support O(1) get size and thus .size() can't be called.\n";
    std::cout << "But can still use non-constant time distance function to get size " << std::distance(myNums2.begin(), myNums2.end()) << "\n";
  }


  // but a workaround is passing the creation of a subrange a size hint
  // assumed to be accurate. if not, undefined behavior
  std::ranges::subrange forward_sr{myNums2, 5};
  if constexpr(std::ranges::sized_range<decltype(forward_sr)>){
    std::cout << "A subrange of a forward list can support O(1) get size with size hints!\n";
  }
  if (forward_sr){
    std::cout << "The subrange can be passes as a boolean to determine if it's empty or not\n";
  }

  // subranges support structured binding
  auto [begin, end]{forward_sr};
  std::for_each(begin, end, log_num);
  std::cout << "\n";

  // advance method
  /// advances subrange forward only to the end.
  forward_sr.advance(2);
  auto [newbegin, newend]{forward_sr};
  std::cout << "after advancing 2 vals: ";
  std::for_each(newbegin, newend, log_num);
  std::cout << "\n";
  forward_sr.advance(90);
  if (forward_sr.begin() == forward_sr.end()){
    std::cout << "At most, we just advance to the end of the subrange.\n";
  }
  

  // if bidirectional range, we can pass negative values to advance but
  // we go backwards. There is no checking from advancing too far back

  // next does not modify subrange in place, returns a new subrange
  // prev does the same, just opposite direction and adds additional compile time checks
  // compiler error if range no bidirectional
  std::vector range1{1, 2, 3, 4, 5};
  std::ranges::subrange A{range1};
  std::ranges::subrange B{A.next(2)};
  std::ranges::subrange C{B.prev(2)};
  std::ranges::for_each(B, log_num);
  std::cout << "\n";
  std::ranges::for_each(C, log_num);
  std::cout << "\n";

  // note general subrange object access through front, back, and [] methods and operator

}