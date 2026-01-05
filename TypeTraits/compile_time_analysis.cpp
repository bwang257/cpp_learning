/*
Introduction to type traits
- type traits + static_assert()
*/

#include <iostream>
#include <type_traits>

// almost all type traits are struct templates
// they accept the type to investigate as a template parameter
// and make the result of that investigation avaialable through the
// static value field

// ** these are all determined at compile time, result available at runtime **
// even if the resulting if statement is not run, it can be invalid (if x not string, x * 2)
// which can lead to compilation errors
// thus, we should use the if constexpr statement, which removes false if code blocks


class Book {};
class Textbook : Book {};

// many more type traits available
template <typename T>
void Function (T x){
  if constexpr (std::is_arithmetic_v<T>){
    std::cout << x * 2 << " is arithmetic\n";
  }
  if constexpr (std::is_pointer_v<T>){
    std::cout << "Input is a pointer\n";
  }
  if constexpr (std::is_class_v<T>){
    std::cout << "Input is a class\n";
  }
  if constexpr (std::is_same_v<Book, T>){
    std::cout << "Input is a Book\n";
  }
  if constexpr(std::is_base_of_v<Book, T>){
    std::cout << "Type is derived from Book\n";
  }
}

// static_assert ensures template is used as expected
template <typename T1, typename T2>
auto Average(T1 x, T2 y){
  static_assert(std::is_arithmetic_v<T1> && std::is_arithmetic_v<T2>, 
    "Average: Arguments must be numeric");
  return (x+y)/2;
}

// reminder: && denotes a forwarding refernece
// comparisons are often stricter than we need
// ex: int y{7} passed in as l-value --> int& --> T& && --> T == int& != int (reference collapsing rules)
// ex: const int != int
template <typename T>
void Print(T&& x){
  if constexpr(std::is_same_v<T, int>){
    std::cout << "Print was passed an int\n";
  }
  if constexpr(std::is_same_v<T, int&>){
    std::cout << "Print was passed an int&\n";
  }
  if constexpr(std::is_same_v<T, const int&>){
    std::cout << "Print was passed a const int&\n";
  }
  if constexpr(std::is_same_v<T, const int>){
    std::cout << "Print was passed a const int\n";
  }
}


// revised to include removal of references and const
template <typename T>
void RevisedPrint(T&& x){

  // using BaseType = std::remove_cvref_t<T>;

  if constexpr (std::is_same_v<int , std::remove_reference_t<T>>){
    std::cout << "RevisedPrint was passed something that's the same as an int after removing references\n";
  }

  // stands for const, volatile, and reference (cvref)
  else if constexpr (std::is_same_v<int, std::remove_cvref_t<T>>){
    std::cout << "RevisedPrint was passed something that's the same as an int after removing cvref\n";
  }
  // not included here: std::remove_const and std::remove_volatile_t
}


// creating our own type traits: is_renderable<T>::value
// general template
/*
slower:
template <typename T>
struct is_renderable {
  static const bool value{false};
};
*/
template <typename>
struct is_renderable : std::false_type {};

class Fish {
  public:
    void Render() {
      std::cout << "Fish: <>((((`>" << std::endl;
    }
};

// specialized template
/* 
slower:
template <>
struct is_renderable<Fish> {
  static const bool value{true};
};
*/
template<>
struct is_renderable<Fish> : std::true_type {};

// implement _v and _t pattern api
// var template that retrieves static member
template <typename T>
constexpr bool is_renderable_v{is_renderable<T>::value};


// render template
template <typename T>
void Render(T param){
  if constexpr(is_renderable_v<T>){
    param.Render();
  } else {
    std::cout << "Not renderable" << std::endl;
  }
}

int main(){

  // C++11
  if (std::is_arithmetic<int>::value){
    std::cout << "int is arithmetic\n";
  }
  // C++17+ concise
  if (std::is_arithmetic_v<double>){
    std::cout << "double is arithmetic too\n";
  }
  if (std::is_arithmetic<std::int32_t>()){
    std::cout << "so is std::int32_t\n";
  }

  Function("Hello World!");
  Function(2342);
  int p{42};
  int* pntr = &p;
  Function(pntr);
  std::cout << "\nBook:" << std::endl;
  Function(Book{});
  std::cout << "\nTextbook:" << std::endl;
  Function(Textbook{});

  // Average("Hello", "World");
  std::cout << '\n' << Average(p, 7) << std::endl;

  std::cout << "\nPrint Function:\n";
  Print(1);
  int z{7};
  Print(z);
  const int i{3};
  Print(i);

  std::cout << "\nRevisedPrint Function:\n";
  RevisedPrint(1);
  RevisedPrint(z);
  RevisedPrint(i);

  // volatile var are var that can be modifeid outside our code
  // ex. external program or hardware
  // prevents compiler from doing optimizations and always get latest value from memory
  volatile int b{42};
  RevisedPrint(b);

  std::cout << "\nOwn type trait:\n";
  Fish myFish;
  Render(myFish);
  Render(42);

  return 0;

  
}