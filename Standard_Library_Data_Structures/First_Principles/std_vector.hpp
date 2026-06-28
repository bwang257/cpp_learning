#pragma once

#include <cstddef>
/*
Notes:
- if (ptr1 - ptr2) discouaraged over == for readability, == has zero overhead, no division risk
- adding to raw ptrs adds the size of the object it points to automatically
*/

template <class T, class allocator = std::allocator<T>>
class vector { 
  public:
    class iterator {

      public:
        // explicit needed so no unintended "Iterator ptr = raw_ptr/nullptr"
        iterator() : ptr(nullptr){}
        explicit iterator(T* p) : ptr{p}{}

        bool operator==(const iterator& other) const noexcept{
          return this->ptr == other.ptr;
        }
        
        std::ptrdiff_t operator-(const iterator& other) const noexcept{
          return this->ptr - other.ptr;
        }

        iterator& operator++() noexcept{ // ++ptr
          ptr += 1;
          return *this;
        }

        iterator operator++(int) noexcept { // ptr++
          // returns copy of old state
          // int is purely a dummy var
          auto temp = *this;
          ptr += 1;
          return temp;
        }
      private:
        T* ptr{nullptr}; 
    };
    static_assert(sizeof(iterator) == 8, "Size incorrect with iterator");


    void push_back(T){
      if (_last == _end){

      }

    }

    size_t size(){
      return _last - _first;
    }

    size_t capacity(){

    }

    bool empty(){
      return this->_first == this->_last;
    }

    T* begin(){
      return this->_first;
    }
    const T* cbegin(){ 
      // implicit conversion to const
      return this->_first;
    }

    T* end(){
      return this->_last;
    }
    const T* cend(){
      // implicit conversion to const
      return this->_end;
    }
  private:
    iterator _first{}; // ptr to first element
    iterator _last{}; // ptr to past last elementI
    iterator _end{}; // ptr to end of allocated block
  
};
static_assert(sizeof(vector<int>) == 24, "");


