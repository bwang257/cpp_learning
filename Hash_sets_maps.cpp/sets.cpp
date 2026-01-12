/*
Introduction to sets in cpp
- getting obj count, removing objects, searching, modifying
- collisions, buckets, load factor, rehashing and reserving
*/

#include <iostream>
#include <unordered_set>
#include <vector>
#include <algorithm>


void Log(int x){ std::cout << x << ", "; }

template <typename t>
void LogSet(std::unordered_set<t>& testSet){
  std::cout << "Buckets: " << testSet.bucket_count() << '\n';
  std::cout << "Size: " << testSet.size() << '\n';
  std::cout << "Load factor: " << testSet.load_factor() << '\n' << std::endl;
}


int main(){

  // create a hash set with values
  std::unordered_set<int> mySet { 1, 2, 3, 3, 4, 5}; // duplicates are ignored

  // create a set from a vector
  std::vector<int> myVec{3, 2, 2, 2, 3, 1, 5, 6, 8};
  std::unordered_set<int> mySet2{myVec.begin(), myVec.end()};

  std::cout << "Set created from vector {3, 2, 2, 2, 3, 1, 5, 6, 8}: ";
  // the container is not ordered
  std::for_each(mySet2.begin(), mySet2.end(), Log);
  std::cout << "\n";


  // inserting items
  // can copy or move-construct on insertion
  std::unordered_set<std::string> newSet;
  std::string Greeting{"Hello"};
  std::string Target{"Everyone"};
  // insert returns a pair (iterato to where we tried to insert, success bool)
  auto [it, wasInserted]{newSet.insert(Greeting)};
  if (wasInserted){
    std::cout << *it << " was inserted into the set\n";
  }
  newSet.insert(std::move(Target));

  // can also insert list of objects
  newSet.insert({"How", "are", "we", "doing"});

  std::vector<std::string> someExtraWords{"Hi", "Brian", "words"};
  newSet.insert(someExtraWords.begin(), someExtraWords.end());

  if (newSet.contains("words")){ // C++20
    std::cout << "words has been added to the set\n";
  }
  if (newSet.count("Hi")){ // prior to C++20
    std::cout << "Hi has also been added to the set\n";
  }

  for (const std::string& S : newSet){
    std::cout << S << ' ';
  }
  std::cout << '\n';
  std::cout << "Size of newSet: " << newSet.size() << "\n";

  // insert range (C++23 concept)
  std::vector<std::string> someExtraWords2{"Hash", "Set", "Map"};
  newSet.insert_range(someExtraWords2);

  // erase item safely (no checks needed)
  int res = newSet.erase("Brian"); // returns 1 or 0
  if (res){
    std::cout << "Brian was removed from the set\n";
  }

  std::cout << "Size of newSet after erasing: " << newSet.size() << "\n";
  newSet.clear();
  std::cout << "Size of newSet after clearing: " << newSet.size() << "\n";
  newSet.insert("SomeWord");

  // find() generators an iterator (end() if not found)
  auto A{newSet.find("SomeWord")};
  if (A == newSet.end()){
    std::cout << "SomeWord was not found in the set\n";
  }
  else {
    std::cout << "Someword was found in the set\n";
  }

  // modifying objects can be difficult as it can mess with the expected position
  // C++17 extract method that transfers ownership of a node to the caller
  // that node is effectively removed from the set
  std::unordered_set Set{1, 2, 3};
  auto Node{Set.extract(3)};
  if (Set.size() == 2){
    std::cout << "Ownership of node with value of 3 transfered to caller\n";
  }
  Node.value() = 4;
  Set.insert(std::move(Node));
  if (Set.size() == 3 && Set.count(4)){
    std::cout << "Node ownership transfered back to the set with new val of 4\n";
  }

  // collisions generally handled through secondary chaining, where each bucket
  // is connected to a linkedlist
  // bucket count changes and rehhashing happens once the container exceeds the max load factor
  std::cout << "\n=== set buckets, load factor, size ===\n";
  std::unordered_set<int> testSet; 
  testSet.max_load_factor(0.75); // can actually specify max load factor
  std::cout << "Configured max load factor: " << testSet.max_load_factor() << "\n";
  LogSet(testSet);
  for (int i = 0; i < 16; i++){
    testSet.emplace(i);
    LogSet(testSet);
  }

  // can rehash to at least a specified num of buckets
  testSet.rehash(500);
  std::cout << "New bucket count: "<< testSet.bucket_count() << '\n';

  // can reserve space for _ items
  std::unordered_set<int> testSet2;
  testSet2.max_load_factor(0.25);
  testSet2.reserve(500); // reserve space for 500 ints
  std::cout << "Bucket count (reserved 500 items, max load 0.25): " << testSet2.bucket_count() << '\n';
  std::cout << "Size of this empty set: " << sizeof(testSet2) << " bytes\n";

}
