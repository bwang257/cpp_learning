/*
Discussion of creating custom iterators using C++20 concepts
*/

// common to define custom iterator within the container's class or struct
// we need to apply c++20 concepts or tags so that we can adapt our iterator to 
// all types of container access patterns (forward/bidirectional/random/continguous)


#include <iostream>
#include <concepts>

class Player {
  public:
    std::string name;
};

class Party {
public:
  Party(Player A, Player B, Player C) : A{A}, B{B}, C{C}{}

  Player A, B, C;

  struct Iterator {
    // application of iterator tags and type aliases
    using iterator_category =
    std::forward_iterator_tag;
    using value_type = Player; // type of obj iterator points at
    using element_type = value_type; // alias for value_type
    using pointer = value_type*; // ptr form of value_type
    using reference = value_type&;
    using difference_type = std::ptrdiff_t; // type used for pointer arithmetic

    Iterator() = default; // not immediately useful, but can add flexibility (only use if somebool true)
    Iterator(Party* ptr, size_t idx) : Party(ptr), idx(idx){}

    // can also write as reference operator*() const ....
    Player& operator*() const{
      if (idx == 0) return Party->A;
      if (idx == 1) return Party->B;
      if (idx == 2) return Party->C;

      throw std::out_of_range{ "Parties can only have 3 players"};
    }

    Player* operator->() const{
      return &operator*();
    }

    // need to implement both for the iterator to be a forward_iterator
    Iterator& operator++(){ // prefix
      idx++;
      return *this;
    }

    Iterator operator++(int){ // postfix
      Iterator temp = *this;
      ++(*this); // use prefix operator
      return temp;
    }

    bool operator==(const Iterator& b) const{
      return Party == b.Party && idx == b.idx;
    }

    private:
      size_t idx;
      Party* Party;
  };

  Iterator begin(){ return Iterator(this, 0); }
  Iterator end(){ return Iterator(this, 3); }
};

// these tags allow us to eaisly work with our iterators at compile time
template <typename T1, typename T2>
void LogIfType(T2&& Iter){
  if constexpr(std::same_as<T1, typename T2::value_type>){
    std::cout << (*Iter).name << "\n";
  }
}

int main(){
  Party party{Player{"Anna"}, Player{"Roderick"}, Player{"Bob"}};

  for (Player& P : party) {
    std::cout << P.name << ", ";
  }
  std::cout << "\n";
  LogIfType<Player>(party.begin());
  LogIfType<int>(party.begin()); // nothing


  // 1) ++ operators have to be supported
  // 2) std:default_initializable concept needs to be satisified
  //     - default-constuctible
  // 3) doesn't actually require implementing ->
  static_assert(std::forward_iterator<Party::Iterator>);
  std::cout << "Our custom iterator satisfied the forward iterator concept!\n";

  static_assert(std::ranges::forward_range<Party>);
  
  // expanding the forward iterator
  std::cout << "To implement a bidirectional iterator, or random access iterator, must implement\n";
  std::cout << "operators such as --, [], + x, -x, then check with\n";
  std::cout << "static assert std::bidirectional_iterator or std::random_access_iterator\n";



}
/*
g++ -std=c++20 custom_iterators.cpp -o run
*/
