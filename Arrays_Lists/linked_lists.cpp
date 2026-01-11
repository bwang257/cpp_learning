/*
Introduction to linkedlists
- foucs on std::forward_list
*/

#include <iostream>
#include <forward_list>
#include <iterator>
#include <string>

class Character {
  public:
    Character(std::string name, int age) : name{name}, age{age}{}
    std::string name;
    int age;

    bool operator==(const Character& other) const {
      return other.name == name && other.age == age;
    }
};

bool under18(Character& character) {
  return character.age < 18;
}

bool isOlder(const Character& A, const Character& B){
  return A.age > B.age;
}

int main(){
  std::forward_list<Character> myList;
  // add existing object
  Character Brian{"Brian", 19};
  Character Aman{"Aman", 19};
  myList.push_front(Brian);
  std::cout << "push_front creates a copy\n";
  std::cout << "Memory address of added element: " << &(*myList.begin()) << ", memory address of original element: " << &Brian << "\n";

  myList.emplace_front("Andrew", 20); // add new object in place, arguments are given to constructor
  myList.insert_after(myList.begin(), Aman); // insert after iterator to first element
  myList.emplace_after(myList.begin(), "Ben", 19);
  myList.emplace_front("Random person", 42);
  myList.pop_front(); // remove first element
  // remove, note overriden == operator
  std::cout << myList.remove(Character{"Aman", 19}) << " Aman of age 19 removed\n"; // C++20 returns num obj removed

  myList.emplace_front("Person1", 17);
  myList.emplace_front("Person2", 16);
  std::cout << myList.remove_if(under18) << " people under age 18 removed\n"; // removes if function is true

  std::cout << "Current size: " << std::distance(myList.begin(), myList.end()) << "\n";
  std::cout << "Front: " << myList.front().name << "\n";
  auto third{std::next(myList.begin(), 2)};
  std::cout << "Accessing third element: " << third->name << " (" << third->age << ")\n";
  std::cout << "Range based loop: ";
  for (Character& c : myList){
    std::cout << c.name << " (" << c.age << "), ";
  }
  std::cout << "\n";

  // remove all objects
  std::cout << "Clearing... ";
  myList.clear();
  std::cout << "New Size: " << std::distance(myList.begin(), myList.end()) << "\n";

  
  std::forward_list myList2{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::cout << "\nElements in myList2: ";
  for (int x : myList2){
    std::cout << x << ", ";
  }
  std::cout << "\n";

  auto eighth = std::next(myList2.begin(), 7);
  myList2.erase_after(eighth); // remove 9

  // can also remove a range, excluding the objects at the starting and ending iterator
  // remove 3 - 6
  auto second = std::next(myList2.begin(), 1);
  auto seventh = std::next(myList2.begin(), 6);
  myList2.erase_after(second, seventh);
  std::cout << "Final Elements in myList2: ";
  for (int x : myList2){
    std::cout << x << ", ";
  }
  std::cout << "\n";

  // sorting
  std::forward_list intList {5, 6, 2, 3, 8, 9};
  std::cout << "\nElements in a new integer list ";
  for (int x : intList){
    std::cout << x << ", ";
  }
  intList.sort();

  std::cout << "\n";
    std::cout << "Sorted Elements in this integer list: ";
  for (int x : intList){
    std::cout << x << ", ";
  }
  std::cout << "\n";


  std::forward_list myList3 {
    Character{"Andrew", 8},
    Character{"Bob", 19},
    Character{"Chris", 5},
    Character{"David", 42},
    Character{"Evan", 90}
  };

  std::cout << "\nElements in new character list: ";
  for (Character& c : myList3){
    std::cout << c.name << " (" << c.age << "), ";
  }
  std::cout << "\n";
  
  // custom sorting with passed in function
  myList3.sort(isOlder);
  std::cout << "Elements in custom sorted new character list: ";
  for (Character& c : myList3){
    std::cout << c.name << " (" << c.age << "), ";
  }
  std::cout << "\n\n";  
}