/*
Compiler-time type deduction
- decltype, std::declval
- template type deduction

g++ -std=c++14 type_deduction.cpp -o run
*/

// decltype asks the compiler what is the type of this expression
// **doesn't evaluate the expression**

// std::declval allows up to work with a hypothetical instance
// as decltype can be cumbersome if the expression requires
// constructing an object with complex constructor arguments

#include <iostream>
#include <utility>
#include <type_traits>

struct mysteriousStruct {
  mysteriousStruct(int val1, int val2, int val3) : field1(val1), field2(val2), field3(val3) {}
  int function2(){return 2;}
  int field1;
  int field2;
  int field3;
};


int function1(){return 1;}

// when the parameter type (ex. const T& for func(const T& val) is neither a ptr or reference)
// ignores argument's reference-ness, const, volatile; passed by value
template <typename T>
void template_by_value1(T val){
  val+=5;
  std::cout << val << "\n";
}


// when passed a const char* const ptr, const of the ptr disregarded
// can then reassign param(val), passed by value
template <typename T>
void template_by_value2(T val){
  const char* x{"New string!"};
  val = x;
  std::cout << val << "\n";
}

// normally arrays decay to ptrs but create paramtype T& allows array to be passed as array reference
// const char [13] ==> T& = const char (&)[13], where T = const char [13]
template <typename T, std::size_t N>
void template_array(T (&arr)[N]) noexcept{
  for (int i{}; i < N; i++){
    std::cout << arr[i];
  }
  std::cout << "\nSize: " << N << "\n";
}

void template_type_deduction(){
  const int x{27};
  const int& y{x};

  // passing a const int& as an arg only means that the arg will not be modified
  // the param can then be modified still
  template_by_value1(y);

  const char* const ptr{"Old string"};
  template_by_value2(ptr); 

  const char name []{"Brian"};
  template_array(name);

  // note that function passed to functions also decay to ptrs 
  // but that isn't explored here
}

void auto_type_deduction(){
  // auto essentially works the same as template type deduction
  // auto --> T, the overall type (ex. const auto&) is the paramtype
  const char* const ptr{"Orig String"};
  auto ptr2{ptr};
  ptr2 = "Modified String";
  std::cout << ptr2 << "\n";

  // applied to universal references + arrays/functions
  int x{3}; // x is l-value
  auto&& uref1{x};
  static_assert(std::is_same<decltype(uref1), int&>::value, "");

  auto&& uref2{27}; // r-value
  static_assert(std::is_same<decltype(uref2), int&&>::value, "");

  const char name []{"Brian"};
  auto& arr{name};
  static_assert(std::is_same<decltype(arr), const char (&)[6]>::value, "");

  // issue that can come up 
  // only difference between auto and template type deduction
  // template type deduction can't deduce brackets unless you specify initializer list
  int a{4};
  auto b = {4};
  if (!std::is_same<decltype(b), decltype(a)>::value){
    if (std::is_same<decltype(b), std::initializer_list<int>>::value){
      std::cout << "auto b = {4} is initialized to type std::initializer_list<int>\n";
    }
  }

  // auto in function returns statement + lambda parameter use template type deduction
  // so passing in {1, 2, 3}, type would not be deduced
}


int main(){
  
  // can use decltype wherever a is expected
  using SomeType = decltype(42);
  SomeType someValue;

  decltype(function1()) anotherValue;

  // decltype limitations ise an object needs to be constructed
  // arbitrary constructor arguments may need to be added
  // gets worse when we won't even know what type we're constructing + constructor arguments
  using SomeType2 = decltype(mysteriousStruct{1, 2, 99}.function2());

  // std::declval works with a hypothetical object
  using someType3 = decltype(std::declval<mysteriousStruct>().function2());

  template_type_deduction();
  auto_type_deduction();
  return 0;
}

