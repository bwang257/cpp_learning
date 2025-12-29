#include <iostream>
#include <string>
#include <memory>
#include <utility>

using std::cout;
using std::endl;
using std::string;

class Book {
public:
    string author;
    string title;
    int pages;
    Book(string title = "Unnamed") : title {title} {
        cout << "Creating book: " << title << endl;
    }
    ~Book(){
        cout<< "Deleted book: " << title << endl;
    }
};


// Can't pass a unique pointer to functions as copy constructor implicitly called
// need to pass by reference
void passUniquePtrByReference(std::unique_ptr<Book> &ptr){
    cout << "   Passing a unique pointer by reference works" << endl;
    return;
}

// smart pointers have .get(), which can returns the raw pointer (no ownership)
void passUniquePtrRaw(Book* ptr){
    cout << "   Passing a unique ptr's raw ptr works" << endl;
    return;
}

// take ownership of another unique pointers
void moveUniquePtr(std::unique_ptr<Book> u_ptr){
    cout << "   Passing a unique ptr through std::move" << endl;

}


int main(){
    std::cout << "=== Unique Pointers ===\n";

    // create unique pointer
    std::unique_ptr<Book> u_pt{std::make_unique<Book>("Book1")};
    cout<< "Functions and Pointers" << endl;
    passUniquePtrByReference(u_pt);

    // get raw ptr from the smart unique pointer
    passUniquePtrRaw(u_pt.get());
    moveUniquePtr(std::move(u_pt));

    cout << "\n";

    // release() does not delete the underlying resource and returns the raw pointer
    // after release is called, get() returns a nullptr
    std::unique_ptr<Book> u_pt2{std::make_unique<Book>("Book2")};
    cout << "Calling release()" << endl;
    Book* rawptr = u_pt2.release();
    delete rawptr;

    // reset() deletes the smart pointer and the underlying resource
    std::unique_ptr<Book> u_pt3{std::make_unique<Book>("Book3")};
    cout << "\nCalling reset()" << endl;
    u_pt3.reset();

    // reset can take an argument for the smart pointer to own a different object
    cout << "\nReset ptr4 to point to book5" << endl;
    std::unique_ptr<Book> u_pt4{std::make_unique<Book>("Book4")};
    cout << "Calling reset with Book5 as an argument" << endl;
    u_pt4.reset(new Book{"Book5"});

    // can swap pointers with swap()
    cout << "\nSwap Smart pointers\nCreating pointer6" << endl;
    std::unique_ptr<Book> u_pt6{std::make_unique<Book>("Book6")};
    cout << "Calling Swap" << endl;
    u_pt6.swap(u_pt4);
    cout << "Pointer 6: " << u_pt6->title << endl;

    // Notes:
    // const pointers cannot be reset() 
    

    std::cout << "\n=== Program ending ===\n";
}



// performance cost of using shared_ptr over unique_ptr?