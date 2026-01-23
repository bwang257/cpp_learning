/*
Introduction to defining ranges using sentinels
*/

#include <iostream>
#include <vector>
#include <algorithm>


// a limitation of end iterators in range ends is end condition only uncovered when running algorithm
// sentinels solve this issue, simply referring to soemthing that can signal an algorithm to end

// for loops are quite verbose and don't generalize well

// range for_each algorithm allows for any sentinel as end point


// can be compared to iterators using == to signal stop
// dont need to define !_ since c++20
// can also define template sentinels
struct Sentinel {
  bool operator==(std::vector<int>::const_iterator Iter) const {
    return Iter == containerEnd || *Iter % 2 == 0;
  }
  std::vector<int>::const_iterator containerEnd;
};

void Log(int x){
  std::cout << x << ", ";
}

template <typename T>
struct PosSentinel {
  bool operator==(T Iter) const{
    return Iter == ContainerEnd || *Iter < 0;
  }

  T ContainerEnd;
};

// handles constructing the sentinel
template <typename T>
class PositiveRange {
public:
  PositiveRange(std::initializer_list<T> Numbers) : Container{Numbers}, Sentinel{Container.end()} {}

  auto begin() const{ return Container.begin(); }
  auto end() const{ return Sentinel; }

private:
  std::vector<T> Container;
  PosSentinel<typename std::vector<T>::const_iterator> Sentinel;
};

int main(){
  std::vector<int> vec1{1, 2, 3, 4, 5, 6};
  std::ranges::for_each(vec1.begin(), vec1.end()-2, Log);
  std::cout << "\n";

  std::vector<int> vec2{1, 3, 5, 671, 37, 38, 401};
  Sentinel s{vec2.end()};
  std::ranges::for_each(vec2.begin(), s, Log);
  std::cout << "\n";

  PositiveRange R{1, 4, 3, 8, -2, 5};
  // applying custom range class, for_each can directly take range object
  std::ranges::for_each(R, Log);
  std::cout << "\n";

  // this for_each algorithm actually returns iterator to where
  // the sentinel was triggered and a reference to the function that we provided
  // this allows us to find where the range ends/what triggered end/size of the range

  auto [in, fun]{std::ranges::for_each(R, Log)};
  std::cout << "\n";

  std::cout << "Object at sentinel: " << *in << "\n";
  std::cout << "Size of range: " << std::distance(R.begin(), in) << "\n";
  std::cout << "Last in range: " << *(in - 1) << "\n";

}


/*
g++ -std=c++20 sentinels.cpp -o run
*/



