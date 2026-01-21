/*
Introduction to standard library function helpers
- concepts
- functional
- std lib functors
*/

#include <iostream>
#include <concepts>
#include <functional> // std::functional container that runs at **runtime**
#include <format>
#include <string>
#include <forward_list>


int func1(){return 1;}
int add(int x, int y) { return x+y;}

// std::invocable ( + auto) allows functors, lambdas, and functions
void call(std::invocable auto func){ std::cout << "Calling func " << func() << "\n"; }

void callIntCompute(std::invocable<int, int> auto func){
  std::cout << "Calling two int argument func: " << func(1, 2) << "\n";
}

// can use std::predicate for when a function returns a bool
template <std::predicate<int, float> T>
void LogPredicate(T Predicate, int x, float y){
  if (Predicate(x, y)){
    std::cout << "Predicate returned true\n"; 
  }
}

// besides predicate, no other way to check return values
// create own concept
template <typename T>
concept TwoIntsToInt = requires(T Callable) {
  { Callable(1, 1) } -> std::same_as<int>;
};

void callFunc(TwoIntsToInt auto Func, int x, int y){
  std::cout << "Calling a function that takes two ints -> int: " << Func(x, y) << '\n';
}

struct functor{
  void operator()(){}
};

void someFunc(){};


// std::function as a member var
class Person{
  public:
    Person(std::invocable auto levelUp): levelUp{levelUp} { }

    void gainXP(int amt){
      xp+=amt;
      if (xp > 100){
        levelUp();  
      }
    }

  private:
    int xp{0};
    std::function<void()> levelUp;
};

int main(){
  call(func1);
  callIntCompute(add);
  LogPredicate([](int x, float y) -> bool { return x > y; }, 5, 4.0f);
  callFunc([](int x, int y) -> int { return x*y; }, 6, 7);

  // function that returns bool after taking in two ints
  std::function<bool(int, int)> function; // note CTAD is possible too

  // check if function container is empty by coercing a boolean
  if (!function){ std::cout << "function container is currently empty\n"; }


  function = [](int x, int y) -> bool { return x == y; };
  std::cout << std::format("4 and 4 are equal: {}\n", function(4, 4)); 

  // std::function does not prescribe type of calllable, allows flexibility
  std::function function2{someFunc};
  function2 = functor{}; // functor
  function2 = []{}; // lambda

  // can "reset" by setting std::function to a null ptr
  if (function2){ std::cout << "function container is not currently empty... "; }
  function2 = nullptr;
  if (!function2){ std::cout << "but now it is\n"; }

  auto l_up {[]{
    std::cout << "Person leveled up! Congrats!\n";
  }};

  Person brian{l_up};
  brian.gainXP(50);
  brian.gainXP(60);


  // brief discussion of std library objects
  std::forward_list Nums{3, 1, 2, 5, 4};

  Nums.sort([](int x, int y) { return x < y; }); // can do this
  // or
  Nums.sort(std::less{}); // std lib object that accepts two vals, returns operator result

  std::cout << "Sorted Container: ";
  for (auto Num : Nums) {
    std::cout << Num << ", ";
  }
  std::cout << "\n";

}