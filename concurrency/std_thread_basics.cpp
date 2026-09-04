// introduction to std::threads

#include <iostream>
#include <thread>
#include <cassert>
#include <algorithm>
#include <vector>

/*
  std::threads are passed functions/anything callable (i.e. soemthing with () operator defined)
  - they can be associated with a single thread, which can be moved to other std::thread objects
  - cannot be copied
  - should be joined or detatched (or wrapped in an RAII idiom)
  - function by creating a temp copy of the passed in function args, which are passed to the func as r values
    - may need to use std::ref to clarify that it should be a reference

  note: be careful of most vexing parse --> use {} or two sets of parentheses
*/

void separate_func_1(){
  // printing the id is implementation dependent
  // comparison operators are defined for ids, allows for determining a main/lead thread, organizing threads, etc.
  std::cout << "Separate function 1 called by thread id: " << std::this_thread::get_id() << '\n';
}

void separate_func_2(){
  std::cout << "This is separate function 2\n";
}


void get_hardware_concurrency(){
  // returns number of threads that can truly run concurrently for a given execution of the program
  unsigned int num_threads = std::thread::hardware_concurrency();
  

  // should handle fallback if the function returns 0 (returns 0 if not computable or well defined)
  num_threads = std::max(num_threads, 1u);
  std::cout << "Number of concurrent hardware threads supported: " << num_threads << '\n';
  std::cout << "Using more than " << num_threads << " leads to oversubscription and can decrease performance\n";
}


// define some function that can be split among many threads 
void accumulate(int start, int end, long long& result){
  long long sum{};
  while (start <= end){
    sum+=start;
    start++;
  }
  result = sum;
}

// RAII wrapper
class joining_thread{
  std::thread t;
  public:
    joining_thread() noexcept = default;
    template <typename Callable, typename... Args>
    explicit joining_thread(Callable&& func, Args&& ... args) : t(std::forward<Callable>(func), std::forward<Args>(args)...) {}

    explicit joining_thread(std::thread t_) noexcept : t(std::move(t_)){}; // threads can be moved
    joining_thread(joining_thread&& other) noexcept : t(std::move(other.t)){};

    joining_thread& operator=(joining_thread&& other) noexcept { 
      if (joinable()) join();
      t = std::move(other.t);
      return *this;
    }

    joining_thread& operator=(std::thread other) noexcept {
      if (joinable()) join();
      t = std::move(other);
      return *this;
    }

    ~joining_thread(){
      if (joinable()) join();
    }

    void swap(joining_thread& other) noexcept {
      t.swap(other.t);
    }

    std::thread::id get_id() noexcept{
      return t.get_id();
    }
    bool joinable(){
      return t.joinable();
    }
    void join(){
      t.join();
    }
    void detatch(){
      t.detach();
    }
    std::thread& as_thread() noexcept {
      return t;
    }
    const std::thread& as_thread() const noexcept{
      return t;
    }
};

int main(){
  std::cout << "Main thread starting\n";
  separate_func_1();
  get_hardware_concurrency();

  // example of using lambdas to combine mult funcs without needing to create 
  // some sort of function objects contianing them
  std::thread my_first_thread([]{
      separate_func_1();
      separate_func_2();
  });
 
  // ensure that the thread is either joined or detatched (esp in exception cases)
  // if detached, ensure that it isn't trying to access local var from the main thread (UB)
  // else std::terminate is called, crashing the entire thread
  assert(my_first_thread.joinable());
  my_first_thread.join(); // this also cleans up any storage associated with the thread. can only be called once


  // using the RAII wrapper
  std::cout << "\n\n==Using the RAII Wrapper==\n";
  int START{};
  int END{100000};
  int NUM_THREADS{4};
  std::vector<long long> results(NUM_THREADS);
  int interval = (END - START)/NUM_THREADS;
  {
    // define own scope so we can see the RAII wrapper in action
    // which joins every thread (in destruction order) before we read results
    std::vector<joining_thread> j_threads(NUM_THREADS);
    for (int idx{}; idx < NUM_THREADS; ++idx){
      int chunk_start = idx * interval + 1;
      // last thread absorbs any remainder left by the truncating division above
      int chunk_end = (idx == NUM_THREADS - 1) ? END : chunk_start + interval - 1;
      j_threads[idx] = joining_thread(accumulate, chunk_start, chunk_end, std::ref(results[idx]));
    }
  }

  long long overall_sum{};
  for (int idx{}; idx < NUM_THREADS; ++idx){
    overall_sum += results[idx];
  }

  std::cout << "Overall sum from " << START << " to " << END << " is " << overall_sum << '\n';
  std::cout << "Main thread terminating\n";
}
