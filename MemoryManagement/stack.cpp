#include <iostream>
#include <string>

class myObject {
public:
    myObject(){
        std::cout << "Creating myObject!\n";
    }
    ~myObject(){
        std::cout << "Destroying myObject :(\n";
    }

    std::string name = "Brian";

};

void testStack();
myObject testMoving();

int main() {
  std::cout << "Program Starting\n";
  testStack();
  myObject test = testMoving();
  std::cout << test.name << std::endl;
  std::cout << "Program Ending\n";
}

void testStack(){
    /**
    allocates memory for obj on the stack. 
    memory is deallocated once stack frame is removed.
    */
    myObject obj;
}

myObject testMoving(){
    /** 
    test moving the object, object is not deleted until the end
    */
    myObject obj;
    return obj;
}