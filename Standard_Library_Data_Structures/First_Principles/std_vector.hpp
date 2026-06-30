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

        // TODO: return by value?
        iterator& operator+(size_t shift){
          std::cout << shift << '\n';
          std::cout << ptr << '\n';
          ptr += shift;
          std::cout << ptr << '\n';
        
          return *this;
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

        // should this be private?
        T* ptr{nullptr}; 
    };
    static_assert(sizeof(iterator) == 8, "Size incorrect with iterator");


    T& operator[](size_t idx){
      return *(_first.ptr + idx);
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

      std::cout << "Push_Back called!\n\n\n\n";

      if (_last == _end){

        std::cout << "First: " <<  _first.ptr << '\n';

        // reallocate memory

        size_t prev_size = this->size();


        size_t new_size = this->size() == 0 ? 1 : 2 * this->size(); // TODO: store as local var or keep
        std::cout << "New capacity: " << new_size << '\n';
        iterator old_start{_first.ptr};
        iterator new_start{new T[new_size]};
        iterator cpy = new_start;


        while (_first < _end){
          *(cpy.ptr) = *(_first.ptr); // TODO: determine if this should be allowed
          cpy += 1;
          _first += 1;
        }
        *(cpy.ptr) = val;
        _last = cpy + 1;
        
        _end.ptr = new_start.ptr + new_size; // can't seem to _end = new_start + new_size
        std::cout << "_end assigned to: " << _last.ptr << '\n';

        if (old_start.ptr){
          std::cout << "UH OH" << '\n';
          std::cout << _first.ptr << '\n';
          std::cout << old_start.ptr << '\n';
          if (prev_size >  1) delete old_start.ptr;
          else delete[] old_start.ptr; 
          std::cout << "We broke through\n";
        }

        _first = new_start;
      } else {
        *(_last.ptr) = val;
        _last.ptr += 1;
      }
    }


    void push_back(T&& val){
      std::cout << "L value push_back was called\n";
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


