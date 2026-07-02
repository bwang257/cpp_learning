#pragma once

#include <cstddef>
#include <stdexcept>

/*
Notes:
- if (ptr1 - ptr2) discouaraged over == for readability, == has zero overhead, no division risk
- adding to raw ptrs adds the size of the object it points to automatically
- we assume the invariant that _first <= _last <= _end is valid
*/

template <class T, class allocator = std::allocator<T>>
class vector { 
  public:
    class iterator {
      public:
        // explicit needed so no unintended "Iterator ptr = raw_ptr/nullptr"
        iterator() : ptr(nullptr){}
        explicit iterator(T* p) : ptr{p}{}

        iterator operator+(size_t shift) const noexcept{
          return iterator{ptr + shift};
        }

        bool operator<(const iterator& other) const noexcept{
          return this->ptr < other.ptr;
        }

        bool operator>(const iterator& other) const noexcept{
          return this->ptr > other.ptr;
        }

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

        iterator& operator+=(size_t rhs){
          this->ptr += rhs;
          return *this;
        }

      private:
        // ideally should be private
        T* ptr{nullptr}; 

        friend class vector;
    };
    static_assert(sizeof(iterator) == 8, "Size incorrect with iterator");


    T& operator[](size_t idx){
      return *(_first.ptr + idx);
    }

    T& at(size_t idx){
      // size_t type automatically checks for non-negative?
      if (idx >= this->size()){
        throw std::out_of_range("Index out of bounds"); // TODO: possible to write without std::to_string? 
      }
      return *(_first + idx);
    }


    void reallocate_mem(size_t new_size){
      // helpful for both push_back/emplace_back
      // and reserve
      iterator old_start{_first.ptr};
      iterator new_start{new T[new_size]};
      iterator cpy = new_start;

      while (_first < _last){
        *(cpy.ptr) = *(_first.ptr);
        cpy += 1;
        _first += 1;
      }

      _first = new_start;
      _last = cpy;
      _end = new_start + new_size;

        // deallocate past memory: must be called with [] bc allocated with new T[sz]
      if (old_start.ptr) delete[] old_start.ptr;
    }
    
    void reserve(size_t sz){
      // simple does nothing if sz less than current size
      if (sz > this->size()) reallocate_mem(sz);
    }

    // void emplace_back(T&& val){
    //   if (_last == _end){
    //     size_t new_size = this->size() == 0 ? 1 : 2 * this->size();
    //     reallocate_mem(new_size);
    //   }
    // }
    
    void push_back(const T& val){
      // l value
      // reallocate memory if necessary
      if (_last == _end){
        size_t new_size = this->size() == 0 ? 1 : 2 * this->size();
        reallocate_mem(new_size);
      }

      *(_last.ptr) = val;
      _last += 1;
    }


    void push_back(T&& val){
      std::cout << "R value push_back was called\n";
      if (_last == _end){

      }

    }

    size_t size(){
      return static_cast<size_t>(_last - _first);
    }

    size_t capacity(){
      return static_cast<size_t>(_end - _first);
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


