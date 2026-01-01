
/**
Often the objects we create must store otehr objects in them.
This can make deep copying expensive. 
*/

/**
Move semantics are simply a performance optimization
The compiler can still fulfill move requests by using the type's
copy semantics. Resource Moved{std::move(A)} will call the Resource copy constructor
*/



#include <iostream>
#include <memory>
#include <vector>

using std::cout;
using std::endl;
using std::vector;


struct SubResource {
  SubResource(){
    cout << "Creating subresource" << endl;
  };

  // copy constructor
  SubResource(const SubResource& source){
    cout << "Copying subresource (expensive!)" << endl;
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
    cout << "Creating resource" << endl;
  }
  
  // copy constructor
  // when we still want to use the original object
  Resource(const Resource& source) : sub{std::make_unique<SubResource>(*source.sub) } {
    cout << "Copying Resource" << endl;
  }

  // move constructor
  /*
  Instead of copying all the subresources to the new object, we just have the new object take control
  of the existing subresources

  shallow copy, transfer ownership of the subresources to the shallow copy.
  modifies original object
  */
  Resource(Resource&& source) : sub{std::move(source.sub)} {
    cout << "Moving Resource\n";
  }

  // move assignment operator
  Resource& operator=(Resource&& source){
    if (&source == this){
      cout << "Same object, skipping move assignmnet\n";
      return *this;
    }
    cout << "Moving by assignment\n";
    sub = std::move(source.sub);
    return *this;
  }

  std::unique_ptr<SubResource> sub;
};

int main(){
  cout << "Resource A:\n";
  Resource A;

  // Unnecessary copying when moving Resource into a vector
  cout << "\nMoving Resource A into a vector:\n";
  vector<Resource> vect;
  vect.push_back(A);

  // std::move() signals to the compiler that its safe to use ur type's move semantiucs
  cout << "\nResource B:\n";
  Resource B{std::move(A)};

  if (!A.sub.get()){
    cout << "Resource A no longer has its subresource\n";
  }

  Resource C;
  cout << "\nMoving B to C\n";
  C = std::move(B);
  if (!B.sub.get()){
    cout<< "Resource B no longer has its subresource\n";
  }

  cout << "\nMoving C to C\n";
  C = std::move(C);

}