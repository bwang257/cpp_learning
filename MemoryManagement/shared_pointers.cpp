/* 
Introduction to shared pointers
*/

#include <iostream>
#include <memory>
#include <string>

using std::string;
using std::cout;
using std::endl;


class Person {
public:
    string name;
    Person(string name = "unnamed") : name{name}{
        cout << "Creating " << name << endl;
    }
    ~Person(){
        cout << "Deleting " << name << endl;
}};

int main(){
    out << "=== Smart Pointers ===\n";
    auto BrianPointer{std::make_shared<Person>("Brian")};
    
    // doing auto BrianPointer2 {std::make_shared<Person>("Brian")};
    // will not properly copy the shared pointer
    // use_count() will be 1 for each of the pointers as they
    // will not be aware of each other
    auto BrianPointer2{BrianPointer};
    
    // use_count() to get number of owners
    out << "# of owners: " << BrianPointer.use_count() << endl;

    // get raw pointer using .get()
    // reset ownership using .reset()
    // transfer ownership using std::move()
    // can also call .swap()

    // underlying resource only deleted if the resource has no owners

    // use std::dynamic_pointer_cast and std::static_pointer_cast, which return std::shared_ptr instances
    // if the case fails, an empty share pointer is returned, evaluates as a boolean


    /**
    Shared pointers are able to share ownership with a different object that the object
    they are pointing at

    The alternative alternative aliasing std::shared_ptr constructor takes two arguments: the object to own (form of a shared_ptr to copy)
    and the object to point at (memory address).
    */


    std::cout << "\n=== Program ending ===\n";
    return 0;
}