/*
Exploration of Recursion and Memoization in C++
*/

#include <iostream>
#include <unordered_map>


int calls1{0};
int calls2{0};

int naiveFibonacci(int n){
  calls1++;
  if (n <= 0){ return 0;}
  if (n == 1){ return 1; }
  if (n == 2){ return 1; }
  return naiveFibonacci(n - 1) + naiveFibonacci(n-2);
}

// requires figuring out how to get a cache key for more complex
// function calls

// A function whose observable behavior changes depending on whether or not something is cached 
// is generally a red flag and should prompt us to reconsider our implementation.

// also be aware of global variables that change and may affect how useful the cache is
// good for pure functions - functions that always output same for same set of args
std::unordered_map<int, int> cache{{0,0},{1,1},{2,1}};
int revisedFibonacci(int n){
  calls2++;
  if (cache.count(n)){return cache[n]; }
  cache[n] = revisedFibonacci(n-1) + revisedFibonacci(n-2);
  return cache[n];
}



// caching. Memoization is example of caching, caching result of specific arguments

int main(){
  // recursion with fibonacci
  std::cout << "w/o memoization: 17th fibonacci number: " << naiveFibonacci(17) << "\n";
  // the number of calls is actually in a fibonnaci sequence: 17 and 16 called once, 15 called twice, 14 called 3 times, etc.
  // recursion creates ** recursion tree **, this has a branching factor of 2 and a recursion dpeth of a 17
  std::cout << "this was determined after " << calls1 << " calls\n"; // exponential scaling

  std::cout << "with memoization: 17th fibonacci number: " << revisedFibonacci(17) << "\n";
  std::cout << "this was determined after " << calls2 << " calls\n"; // linear scaling

}
