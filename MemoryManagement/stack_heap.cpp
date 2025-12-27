#include <iostream>
#include <string>

class myObject {
public:
    std::string name{"Brian"};

    myObject(){
        std::cout << "Creating myObject!\n";
    }
    myObject(std::string entered_name) : name(entered_name){
        std::cout << "Creating object with name " << name << std::endl;
    }
    ~myObject(){
        std::cout << "Destroying myObject " << name << std::endl;
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
  std::cout << "Calling testMoving\n";
  myObject test = testMoving();
  test.name = "MovedObject";
  std::cout << test.name << std::endl;

  std::cout << "Creating object on the heap\n";
  // memory on stack used to store pointer to heap object
  myObject* heapObject{new myObject{createJeff()}};
  std::cout << heapObject->name << std::endl;
  std::cout << "Deleting object on the heap\n";
  delete heapObject;
  
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