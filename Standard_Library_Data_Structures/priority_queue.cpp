/*
Intro to std::priority_queue
*/


#include <iostream>
#include <queue>
#include <vector>

// is a container adaptor
// default underlying container is vector
// underlying data structure has to support random access iterators 
// and some key methods (push_back, pop_back, front)


// no dynamic priority or reprioritization - look for custom implmentation or third part
// if change element inserted, will not be repositioned accordingly

int main(){
  std::vector<int> Source{1,2,3};
  std::priority_queue<int> Numbers{{}, std::move(Source)}; // {} for no custom compare func, move to avoid copying Source
  
  Numbers.emplace(4);
  int x = 5;
  int y = 6;
  Numbers.push(x);
  Numbers.push(std::move(y));

  // push_range is a c++23 feature
  std::vector Range{7, 8, 9};
  Numbers.push_range(Range);
  
  std::cout << "The current size of the queue is " << Numbers.size() << "\n";
  std::cout << "The top of the queue is " << Numbers.top() << "\n";
  Numbers.pop();
  std::cout << "The top of the queue is now " << Numbers.top() << "\n";

  // custom lambda function for comparing
  auto Comparer{[](int x, int y) {return x < y; }};

  // note 2 additional optional args
  std::vector<int> Source2{1,2,3,4,5,6,7,8};
  std::priority_queue<int, std::vector<int>, decltype(Comparer)> pq{Comparer, Source2};
  while (!pq.empty()){
    std::cout << pq.top() << ", ";
    pq.pop();
  }
  std::cout << "\n";
}