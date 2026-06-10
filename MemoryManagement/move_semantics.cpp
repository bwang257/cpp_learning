/*
Move Semantics in C++

Deep copying can be expensive - performance optimization occurs 
using move semantics

The compiler can still fulfill move requests by using the type's
copy semantics. Resource Moved{std::move(A)} will call the Resource copy constructor

g++ move_semantics.cpp -o run
*/

#include <iostream>
#include <memory>
#include <vector>


struct SubResource {
  SubResource(){
    std::cout << "Creating subresource" << '\n';
  };

  // copy constructor, l-value
  SubResource(const SubResource& source){
    std::cout << "Copying subresource (expensive!)" << '\n';
  }
};

struct Resource {
  
  // if raw ptrs used, this can lead to issue if the moved-from object deletes the subresource
  // owned by the owned to object
  // fixed by changing sub to a nullptr in the move constructor
  // ~Resource(){
  //   delete sub;
  // }

  Resource(){
    std::cout << "Creating resource" << '\n';
  }
  
  // copy constructor -  when we still want to use the original object, l value
  Resource(const Resource& source) : sub{std::make_unique<SubResource>(*source.sub) } {
    std::cout << "Copying Resource" << '\n';
  }

  // move constructor
  /*
  Instead of copying all the subresources to the new object, we just have the new object take control
  of the existing subresources

  shallow copy, transfer ownership of the subresources to the shallow copy.
  modifies original object

  takes in rvalue reference
  */
  Resource(Resource&& source) : sub{std::move(source.sub)} {
    std::cout << "Moving Resource\n";
  }

  // move assignment operator, rvalue reference
  Resource& operator=(Resource&& source){
    if (&source == this){
      std::cout << "Same object, skipping move assignmnet\n";
      return *this;
    }
    std::cout << "Moving by assignment\n";
    sub = std::move(source.sub);
    return *this;
  }

  std::unique_ptr<SubResource> sub;
};

int main(){
  std::cout << "Resource A:\n";
  Resource A;

  // Unnecessary copying when moving Resource into a vector
  std::cout << "\nMoving Resource A into a vector:\n";
  std::vector<Resource> vect;
  vect.push_back(A); // note copying subresource first

  // std::move() signals to the compiler that its safe to use your type's move semantiucs
  std::cout << "\nResource B:\n";
  Resource B{std::move(A)};

  if (!A.sub.get()){
    std::cout << "Resource A no longer has its subresource\n";
  }

  std::cout << "\nResource C\n";
  Resource C;
  std::cout << "\nMoving B to C\n";
  C = std::move(B);
  if (!B.sub.get()){
    std::cout<< "Resource B no longer has its subresource\n";
  }

  std::cout << "\nMoving C to C\n";
  C = std::move(C);

}