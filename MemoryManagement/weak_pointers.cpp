/* 
Introduction to weak pointers - smart ptrs without ownership
Does not include entire API: see more https://en.cppreference.com/cpp/memory/weak_ptr

g++ weak_pointers.cpp -o run
*/

#include <memory>
#include <iostream>
#include <cassert>

/*
Useful when an object only needs to be accessed only if it exists, and it may be deleted any time by
someone else. Can also be used to break reference cycles
*/

int main() {
    auto SharedPtr { std::make_shared<int>(42) };
    std::weak_ptr<int> WeakPtr{SharedPtr}; 

    std::cout << "Size: " << sizeof(WeakPtr) << " bytes\n";
    
    // can't directly dereference, need to convert to shared_ptr with lock()
    // lock attempts to create a temporary std::shared_ptr
    auto SharedPtr2{WeakPtr.lock()};
    std::cout << "Weak ptr currently points to " *SharedPtr2 << '\n';

    // expired() and use_count() methods
    SharedPtr.reset();
    std::cout<< "\nSharedPtr has been reset" << '\n';
    if (WeakPtr.expired()) std::cout << "The underlying resource has be deallocated" << '\n';
    std::cout << "The underlying resource has " << WeakPtr.use_count() << " owners\n" << '\n';


    // can't convert weak ptr to bool
    std::shared_ptr<int> SharedPtr3{WeakPtr.lock()};
    assert(SharedPtr3);

    // access underlying object of a weakptr under conditions that we do not know whether
    // the underlying resource has expired. This is referred to as locking the weak ptr

    if (std::shared_ptr<int> LockedPtr{WeakPtr.lock()}) {
        std::cout << "The number is " << *LockedPtr << '\n';
    } else {
        std::cout << "\nThe pointer has expired" << '\n';
    }
}


