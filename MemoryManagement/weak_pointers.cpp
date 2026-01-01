/* 
Introduction to weak pointers
*/

#include <memory>
#include <iostream>

using std::cout;
using std::endl;

/*
Key Advantage: ability to know whether a ptr has expired. crucial layer of awareness in larger projects
*/

int main() {
    auto SharedPtr { std::make_shared<int>(42) };
    std::weak_ptr<int> WeakPtr{SharedPtr};

    // expired() and use_cout() methods
    SharedPtr.reset();
    cout<< "SharedPtr has been reset" << endl;
    if (WeakPtr.expired()) cout << "The underlying resource has be deallocated" << endl;
    cout << "The underlying resource has " << WeakPtr.use_count() << " owners\n" << endl;

    // access underlying object of a weakptr under conditions that we do not know whether
    // the underlying resource has expired. This is referred to as locking the weak ptr
    if (std::shared_ptr<int> LockedPtr{WeakPtr.lock()}) {
        std::cout << "The number is " << *LockedPtr << endl;
    } else {
        std::cout << "\nThe pointer has expired" << endl;
    }
    return 0;
}


