#pragma once

#include <cstddef>
#include <stdexcept>

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


    T& operator[](size_t idx){
      return *(_first + idx);
    }

    T& at(size_t idx){
      // size_t type automatically checks for non-negative?
      if (idx >= this->size()){
        throw std::out_of_range("Index out of bounds"); // possible to write without std::to_string? 
      }
      return *(_first + idx);
    }


    void emplace_back(T&){

    }

    void push_back(const T& val){
      if (_last == _end){
        // reallocate memory
        size_t new_size = 1 << this->size();
        iterator new_start{new T[new_size]};
        if (_first->ptr) delete[] _first->ptr; 
        // TODO
      }
    }


    void push_back(T&& val){
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


