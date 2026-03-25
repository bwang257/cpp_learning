/*
Binary Serialization in C++
- using Cereal (which supports different data formats)
*/

// Serialization is process of converting objects to a format to be stored or transmitted
// binary serialization more compact and serialization/deserialization is faster

#include <iostream>
#include <cereal/archives/binary.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <filesystem>
#include <cassert>

// to de/serialize stl types 
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>

// for user-defined types
#include <cereal/access.hpp>

// for polymorphism
#include <cereal/types/polymorphic.hpp>

/*
endianness ==> how computers ready binary data
if know that binary has to be used by computers with different endianness
#include <cereal/archives/portable_binary.cpp instead --> but larger, slower to de/serialize
*/

void delete_savefile(){
  try {
    std::filesystem::remove("Savefile");
  } catch (const std::filesystem::filesystem_error& e){
    std::cerr << "Error: " << e.what() << '\n';
  }
}

void serialization_basics(){
  // output archives serialize objects, send to output stream
  // these archives behave like streams

  std::ofstream File{"SaveFile"};
  cereal::BinaryOutputArchive OArchive(File);

  int val1{42};
  double val2{3.14};
  bool b1{true};

  OArchive(val1, val2); // can serialize many at once 
  OArchive(true); // or one at a time

  // stl types (need to include headers)
  std::string s1{"Hello"};
  std::vector<int> someInts{1, 4, 5, 6};
  OArchive(s1, someInts);

  // can't serialize raw ptrs -> can do smart pointers
  auto ptr{std::make_unique<int>(42)}; 
  OArchive(ptr); // heap deallocated and reallocated when deserialized
}

void deserialization_basics(){
  // input archives deserealize, creating objects
  std::ifstream File{"SaveFile"};
  cereal::BinaryInputArchive IArchive(File);

  // deserialization must be in the same order the data was serialized
  // otherwise unpredictable behavior or crashes

  int val1;
  double val2;
  bool b1;
  std::string s1;
  std::vector<int> vec;
  std::unique_ptr<int> ptr;

  std::vector<int> testvec = {1, 4, 5, 6};

  IArchive(val1);
  IArchive(val2);
  IArchive(b1);
  IArchive(s1, vec);
  IArchive(ptr);

  assert(val1 == 42);
  assert(val2 == 3.14);
  assert(b1);
  assert(s1 == "Hello");
  assert(vec == testvec);
  assert(*ptr == 42);

  delete_savefile();
}

class Data{
  public:
    Data() = delete;
    Data(int val1, int val2) : val1{val1}, val2{val2} {}
    Data(int val1, int val2, std::string val3) : val1{val1}, val2{val2}, val3{val3} {}

    int val1;
    int val2;
    std::string val3{""};

  private:
    // cereal first default constructs, then loads data
    // can either do default constructor, define static load_and_construct, or use private default constructor
    friend class cereal::access;
    
    // only called when deserializing through a smart ptr
    template <class Archive>
    static void load_and_construct(Archive& input, cereal::construct<Data>& construct){
      std::cout << "Load_and_construct called!\n";
      // temp vars to hold data
      int t1;
      int t2;

      input(t1, t2); 
      construct(t1, t2); // call constructor, Data object is now constructed
      
      // construct points to created object
      std::cout << "Data object initialized with values: " << construct->val1 << ", " << construct->val2 << '\n';
      
      input(construct->val3);
      std::cout << "Defined constructed object's val3 as \"" << construct->val3 << "\"\n";
    }

    // can define load and save functions (typically do not want to be part of public api)
    // can be combined into a serialize function
    template <class Archive>
    void serialize(Archive& stream){
      stream(val1, val2, val3);
    }
};

/*
can also define specialization for the LoadAndConstruct struct
in cereal namespace

namespace cereal{
  template<>
  struct LoadAndConstruct<Data>{
    template<class Archive>
    static void load_and_construct(Archive& input, cereal::construct<Data>& construct){
      int t1, t2;
      std::string t3;
      input(t1, t2, t3);
      construct(t1, t2, t3);
    }
  }
}
*/

// Note: we can apply class versioning by defining a static inline
// version in that we also serialize. When we load, we check what version
// and implement backwards compatability

/*
Can also use the macro CEREAL_CLASS_VERSION(Data, 2)
the load function becomes  void load(Archive& Data, std::uint32_t ArchiveVersion) 
need to also add std::uint32_t to the save, even if not used
(need for compatibility between serialized data and load function)
*/

class Character{
  public:
    Character() = default;
    Character(std::string name, int level) : name{name}, level{level}{}
    virtual ~Character() = default;
    std::string name;
    int level;
  
  private:
    friend class cereal::access;
    template <class Archive>
    void serialize(Archive& data){
      data(name, level);
    }
};

class Animal : public Character{
  public:
    Animal() = default;
    Animal(std::string name, int level, bool isHostile) : Character(name, level), isHostile{isHostile}{}
    bool isHostile;

  private:
    friend class cereal::access;
    template <class Archive>
    void serialize(Archive& data){
      // serialize base class members, can do using cereal::base_class and cereal::virtual_base_class
      data(cereal::base_class<Character>(this), isHostile);
    }
};

// if working deserializing an animal to a character ptr
// cereal needs a little more help. we use macros
// if using cereal::virtual_/base_class, these macros are optional
CEREAL_REGISTER_TYPE(Animal);
CEREAL_REGISTER_POLYMORPHIC_RELATION(Character, Animal);

void more_complex_types(){
  // custom types + inheritance


  // serialize
  {
    std::ofstream File{"Savefile"};
    cereal::BinaryOutputArchive OArchive(File);

    auto d1_ptr{std::make_shared<Data>(42, 47, "Hello")};

    Animal rabbit{"rabbit", 12, false};
    Animal rat{"rat", 7, true};
    OArchive(d1_ptr, rabbit, rat);
  }
  // deserialize
  {
    std::ifstream File{"Savefile"};
    cereal::BinaryInputArchive IArchive(File);

    // data has no default constructor so load via shared_ptr/unique_ptr
    std::shared_ptr<Data> d1_ptr;
    Animal a1;
    Animal a2;
    IArchive(d1_ptr, a1, a2);
    assert(d1_ptr->val1 == 42 && d1_ptr->val2 == 47);
    assert(d1_ptr->val3 == "Hello");
    assert(a1.name == "rabbit" && a1.level == 12 && !a1.isHostile);
    assert(a2.name == "rat" && a2.level == 7 && a2.isHostile);

    delete_savefile();
  }
}

int main(){
  serialization_basics();
  deserialization_basics();
  more_complex_types();


  std::cout << "\nAll assertions passed!\n\n";

}