/*
Intro to std::queue
*/

#include <iostream>
#include <queue>
#include <list>
#include <vector>

class Person {
  public:
    Person(std::string name) : name{name} {};
    std::string name;
};


// std::queue is a container adaptor, does not implment the storage mechanism
// the underlying container is a deque, can change the underlying containers by passing in a 
// second template arg: std::queue<Person, std::list>
// underlying container just needs to have some key methods
int main(){
  std::queue<int> Numbers; 
  for (int i = 1; i < 6; i++) { Numbers.push(i); }
  std::cout << "Size of a 5 int std::queue: " << sizeof(Numbers) << "\n";

  // initialize queue from another container
  // can construct queue from certain types of containers
  std::queue<int> Copy{Numbers};
  std::queue Move{std::move(Numbers)}; // CTAD

  std::list Nums{1, 2, 3, 4};
  std::queue NumsQueue{Nums};

  // construction from iterators, c++23
  std::vector<int> vec{3, 232, 35, 6, 32, 5};
  std::queue vecQueue{vec.begin(), vec.end()};

  // adding objects, FIFO
  std::queue<Person> cvec;
  Person brian{"Brian"};
  Person aman{"Aman"};
  cvec.push(brian);
  cvec.emplace("Andrew");
  cvec.push(std::move(aman));

  // more methods
  std::cout << "There are " << cvec.size() << " elements in this queue\n";
  std::cout << "The first element in the queue is: " << cvec.front().name << "\n";
  std::cout << "The last element in the queue is: " << cvec.back().name << "\n";
  cvec.pop();
  std::cout << "After popping, the first element in the queue is: " << cvec.front().name << "\n";

}