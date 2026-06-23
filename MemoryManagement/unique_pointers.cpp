/* 
Introduction to unique pointers

g++ unique_pointers.cpp -o run
*/

#include <iostream>
#include <string>
#include <memory>
#include <utility>
#include <cassert> 

class Book {
public:
    std::string author{""};
    std::string title{""};
    int pages{-1};

    Book(std::string title = "Unnamed"): title{title} {
        std::cout << "Creating book: " << title << '\n';
    }
    ~Book(){
        std::cout<< "Deleting book: " << title << '\n';
    }
};


// Can't pass a unique pointer to functions as copy constructor implicitly called
// need to pass by reference, must be const
void passUniquePtrByReference(const std::unique_ptr<Book> &ptr){
    std::cout << "   Passing a unique pointer by reference works: " << ptr.get() <<  '\n';
}

// smart pointers have .get(), which can returns the raw pointer (no ownership)
void passUniquePtrRaw(Book* ptr){
    std::cout << "   Passing raw ptr: " << static_cast<const void*>(ptr) << '\n';
}

// take ownership of another unique pointers
// pass by value, invoke using std::move
void moveUniquePtr(std::unique_ptr<Book> u_ptr){
    std::cout << "   Passing a unique ptr through std::move: " << u_ptr.get() << '\n';
}


int main(){
    std::cout << "=== Unique Pointers ===\n";

    // create unique pointer
    std::unique_ptr<Book> u_pt{std::make_unique<Book>("Book1")};
    std::cout<< "Functions and Pointers" << '\n';
    passUniquePtrByReference(u_pt);

    // get raw ptr from the smart unique pointer
    passUniquePtrRaw(u_pt.get());
    moveUniquePtr(std::move(u_pt));

    std::cout << "\n";

    // release() does not delete the underlying resource and returns the raw pointer
    // after release is called, get() returns a nullptr
    std::unique_ptr<Book> u_pt2{std::make_unique<Book>("Book2")};
    std::cout << "Calling release()" << '\n';
    Book* rawptr = u_pt2.release();
    assert(!u_pt2);
    std::cout << "Rawptr pts to: " << rawptr->title << '\n';
    delete rawptr;

    // reset() deletes the smart pointer and the underlying resource
    std::unique_ptr<Book> u_pt3{std::make_unique<Book>("Book3")};
    std::cout << "\nCalling reset()" << '\n';
    u_pt3.reset();
    assert(!u_pt3);

    // reset can take an argument for the smart pointer to own a different object
    std::cout << "\nReset ptr4 to point to book5" << '\n';
    std::unique_ptr<Book> u_pt4{std::make_unique<Book>("Book4")};
    std::cout << "Calling reset with Book5 as an argument" << '\n';
    u_pt4.reset(new Book{"Book5"});

    // can swap pointers with swap()
    std::cout << "\nSwap Smart pointers\nCreating pointer6" << '\n';
    std::unique_ptr<Book> u_pt6{std::make_unique<Book>("Book6")};
    std::cout << "Calling Swap" << '\n';
    u_pt6.swap(u_pt4);
    std::cout << "Pointer 6: " << u_pt6->title << '\n';

    // Notes:
    // const pointers cannot be reset() 
    

    std::cout << "\n=== Program ending ===\n";
}



// performance cost of using shared_ptr over unique_ptr?