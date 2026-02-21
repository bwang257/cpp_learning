/*
std::priority_queue

Compile with:
g++ -std=c++23 priority_queue.cpp -o run
*/

#include <iostream>
#include <utility>
#include <queue>
#include <vector>
#include <cassert>

// is a container adaptor, with default container vector and max heap implementation
// underlying data structure has to support random access iterators 

// no dynamic priority or reprioritization - look for custom implmentation or third part
// if change element inserted, will not be repositioned accordingly

// technically 3 parameters: type of element, conatiner, and comparator type. If use default
// comparator, only need to specify type of element

void max_heap(){
  std::priority_queue<int> max_heap; // std::less implemented by default
  max_heap.push(4); 
  max_heap.push(3); 
  max_heap.push(2); 
  std::cout << "Current max: " << max_heap.top() << "\n";

  // lambda for max heap implementation on second element
  auto comp_second_val{[](std::pair<int, int> p1, std::pair<int, int> p2){ 
    if (p1.second == p2.second) return p1.first < p2.first;
    return p1.second < p2.second; 
  }};

  // pair implementation
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(comp_second_val)> pair_mh(comp_second_val);
  pair_mh.push({1,2});
  pair_mh.push({2,2});
  pair_mh.push({8,1});
  assert(pair_mh.top().first == 2 && pair_mh.top().second == 2);
  std::cout << "\n";
}

void min_heap(){
  // pair implementation of max heap
  std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int,int>>> pair_minheap;
  std::vector<std::pair<int, int>> my_pairs{{1, 5}, {3, 4}, {7, 2}, {1, 4}, {4, 2}, {6, 9}};

  for (const auto& pair : my_pairs) pair_minheap.push(std::move(pair));
  std::cout << "Pairs in pair minheap: ";
  while (!pair_minheap.empty()){
    const auto& curr_pair = pair_minheap.top(); // return const std::pair<int, int> reference, auto uses template type deduction
    std::cout << "(" << curr_pair.first << ", " << curr_pair.second << "), ";
    pair_minheap.pop();
  }
  std::cout << "\n";
  std::cout << "\n";
}


int main(){
  max_heap();
  min_heap();

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