/*
Introduction to Function Templates
*/

#include <iostream>

using std::cout;
using std::endl;


template <typename T>
T Average(T x, T y){
  return (x+y)/2;
}

// can specify default values
// return type doesn't need to be specified as t1 or t2, let compiler figure it out
// we can also use simply auto as the return type or (shown below) decltype
// decltype needs to come after the function definition so that the parameters have been seen
template <typename t1 = int, typename t2 = t1>
auto modifiedAverage(t1 x, t2 y) -> decltype((x+y)/2) {
  return (x+y)/2;
}

// C++20 feature: abbrieviated function templates
auto autoAverage(auto x, auto y){
  return (x+y)/2;
}


int main(){
  // note that int is the template argument
  // 1 and 2 are the function arguments
  // behind the scences, the compiler instantiates the template
  // but substituting argument int/float into every location where we the parameter
  cout << "Output of Average<int>(1,2): " << Average<int>(1,2) << endl;
  cout << "Output of Average<float>(1,2): " << Average<float>(1,2) << endl;

  // Template Argument deduction
  cout << "Template argument deduction - Output of Average(1,2): " << Average(1,2) << endl;

  // output using decltype and auto:
  cout << modifiedAverage(1.5, 6.777745) << endl;
  cout << autoAverage(1.5, 6.777745) << endl;
  return 0;

}