/* 
Exploration of stack vs heap
*/

#include <iostream>
#include <string>

class myObject {
public:
    std::string name{"Brian"};

    myObject(){
        std::cout << "Creating myObject!\n";
    }
    myObject(std::string entered_name) : name(entered_name){
        std::cout << "Creating object with name " << name << '\n';
    }
    ~myObject(){
        std::cout << "Destroying myObject " << name << '\n';
    }
};


myObject createJeff(){
    return myObject{"Jeff"};
}


void testStack();
myObject testMoving();

int main() {
  std::cout << "Calling testStack\n";
  testStack();
  std::cout << '\n';

  std::cout << "Calling testMoving\n";
  myObject test = testMoving();
  test.name = "MovedObject";
  std::cout << "Returned\n";
  std::cout << '\n';

  std::cout << "Creating object on the heap\n";
  // memory on stack used to store pointer to heap object
  myObject* heapObject{new myObject{createJeff()}};
  std::cout << heapObject->name << '\n';
  std::cout << "Deleting object on the heap\n";
  delete heapObject;
  
  std::cout << "\nProgram Ending\n";
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
    std::cout << "Returning\n";
    return obj;
}