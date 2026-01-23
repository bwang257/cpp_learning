/*
Introduction to perfect forwarding and std::forward
*/

#include <iostream>
#include <type_traits>
#include <string>

class Character {
public:
  Character() {}
  Character(const Character& Original) { // takes in l-value
    std::cout << "Copying\n";
  }
  Character(Character&& Original) { // takes in r-value
    std::cout << "Moving\n";
  }
};


// && forwarding reference
// here it is also a universal reference as it is able to capture both l and r values
// below is an intermediate template function like std::make_shared or emplace

// std::decay removes references and const/volatile modifiers
// but this still calls copy constructor (l-value constructor)
template <typename t>
std::decay_t<t> build_func(t&& obj){
  return std::decay_t<t>(obj);
}


// Perfect forwarding is the process of forwarding arguments 
// to other functions in a way that respects their original value category 
template <typename t>
std::decay_t<t> revised_build_func(t&& obj){
  return std::decay_t<t>(std::forward<t>(obj));
}

class book {
  public: 
    book(std::string title, int len) : title{title}, length{len} {
      std::cout << "Constructing book " << title << " with length " << length << "\n";
    }
    book(const book& orig) : length{orig.length}, title{orig.title} {
      std::cout << "Copying book " << this->title << " with length " << length << "\n";
    }
    book(book&& orig) : length{orig.length}, title{orig.title} {
      std::cout << "Moving book " << this->title << " with length " << length << "\n";
    }
    std::string title;
    int length;
};

// working with variadic functions
template <typename T, typename... Args>
std::decay<T>::type build_book(Args&&... arguments){ // universal reference
  return std::decay_t<T>{std::forward<Args>(arguments)...};
}

int main(){
  Character A;
  Character mychar{build_func(std::move(A))}; // copies, despite l-value

  Character B;
  Character mychar2{revised_build_func(B)}; // copies with l-value
  Character mychar3{revised_build_func(std::move(B))}; // moves with r-value

  using namespace std::string_literals;
  book a{build_book<book>("Effective Modern C++"s, 337)};
  book b{build_book<book>(a)};
  book c{build_book<book>(std::move(a))};

}