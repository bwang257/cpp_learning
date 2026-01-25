/*
Introduction to Parallel Algorithm Execution
*/

/*
due to compatibility issues, compile with:
g++-15 -std=c++23 parallelism.cpp -o run -I$(brew --prefix tbb)/include -L$(brew --prefix tbb)/lib -ltbb
*/

// a stream of execution is called a thread
// concurrency breaks a program into multiple threads
// breaking program into threads gives OS more flexibility to run our program
// in a way that makes better use of the available hardware


// we can use standard library algorithms to implement multi-threading using execution policies
// note use of iterator based std::for_each algorithm here, c++23 range-based algorithms
// do not suppor texecution policies yet

#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <sstream>
#include <tbb/parallel_for_each.h>

void slowFunction(int num){
  using namespace std::chrono_literals;
  std::this_thread::sleep_for(1s);
  std::ostringstream oss;

  // doing something like std::cout << "number: " << num is not threadsafe because
  // we could end up with something like 
  /*
  Number: Number: 1
  Number: 3
  2
  */

  // this requires us to make our processes atomic - code running in other threads cannot divide or 
  // cut into our code

  //A bug where our program exhibits undesirable behavior based on the order of task execution is 
  // commonly called a race condition. May only happen 1% of the time

  // use of oss here is threadsafe, local var
  oss << "Number: " << num << " (thread: " << std::this_thread::get_id() << ")\n";
  std::cout << oss.str();
}

int main(){
  std::vector vec{1, 2, 3, 4, 5};
  
  std::cout << "Main Thread: " << std::this_thread::get_id() << '\n';

  // using tbb because using std::execution::par is executing on the
  // same thread, compatibility issue on macOS I'm assuminng

  // note that parallel execution policity doesn't guarantee parallel execution
  // multithreading requires overhead and platform may decide sequential exeuction is more performant
  tbb::parallel_for_each(vec.begin(), vec.end(), slowFunction);

  // output out of order, random
  // because threads running concurrently are acessing or operating 
  // on the same resources and we don't know the order that this will happen
}
