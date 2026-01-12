/*
Overview of std::unordered_map
*/

#include <iostream>
#include <unordered_map>
#include <string>


template <typename t>
void LogMap(std::unordered_map<t, t>& testMap){
  std::cout << "Buckets: " << testMap.bucket_count() << '\n';
  std::cout << "Size: " << testMap.size() << '\n';
  std::cout << "Load factor: " << testMap.load_factor() << '\n' << std::endl;
}



int main() {
  using std::unordered_map, std::string;

  unordered_map<string, string> Map{
    {"Bob", "robert@example.com"},
    {"Anna", "anna@example.com"},
    {"Dave", "dave@example.com"},
  };

  std::cout << "Size: " << Map.size() << '\n';
  if (Map.contains("Bob")){ // C++20
    std::cout << "Map contains Bob mapped to " << Map["Bob"] << '\n';
  }
  if (Map.count("Anna")){
    std::cout << "Map contains Anna mapped to " << Map["Anna"] << '\n';
  }

  // if [] operator used on unknown key, it will construct and add the key
  Map["Brian"];
  // not undefined or junk behavior, mapped to default val of ""
  // if was int, map to default of 0
  std::cout << "Map[\"Brian\"]: "<< Map["Brian"] << std::endl; 

  // can also access values using at
  try {
    Map.at("Steve");
  } catch (std::out_of_range& e){
    std::cout << "Steve is not in the map: " << e.what() << "\n";
  }

  // find returns iterator to key-val pair
  auto it{Map.find("Dave")};
  if (it == Map.end()){
    std::cout << "Could not find Dave in the map\n";
  } else {
    auto [key, value]{*it};
    std::cout << "Key: " << key << ", Value: " << value << "\n";
  }

  // inserting elements
  std::pair<string, string> Andrew{"Andrew", "Andrew@gmail.com"};
  Map.insert(Andrew);
  Andrew.second = "Andrew1@gmail.com";

  // insert_or_assign returns pair iterator, bool of whether inserted (false: key updated)
  auto [it1, wasInserted] = Map.insert_or_assign("Andrew", "Andrew1@gmail.com"); // c++ 17
  if (!wasInserted){
    std::cout << it1->first << " already existed - its value is now " << it1->second << "\n";
  }

  // emplace
  Map.emplace("Ben", "Ben@gmail.com");

  // try_emplace() only adds entry if there is not key already
  auto [it2, wasSuccessful] = Map.try_emplace("Ben", "Ben2@gmail.com");
  std::cout << "Ben is still mapped to " << Map["Ben"] << '\n';
  if (!wasSuccessful){
    std::cout << "The container already had the key " << it2->first << " with value: " << it2->second << '\n';
  }

  // removing values
  // Map.clear(); // removes all values
  Map.erase("Ben"); // removes Ben key
  

  // editing keys using extract() method C++17
  auto Node {Map.extract("Bob")};
  std::cout << std::format("Extracted key: {}, Extracted value: {}\n", Node.key(), Node.mapped());
  Node.key() = "Robert";
  Map.insert(std::move(Node)); // transfer ownership back to the map
  std::cout << std::format("Updated node: key - Robert, value - {}\n", Map["Robert"]);

  // map iteration
  std::cout << "Complete map:\n";
  
  // ensure we are passing by reference, not by copy of the value
  for (const auto& Pair : Map){ // can also use structured binding with [key, value]
    std::cout << std::format("Key: {}, Value: {}\n", Pair.first, Pair.second);
  }

  // buckets, load factor, and rehasing
  std::cout << "\n=== map buckets, load factor, size ===\n";
  std::unordered_map<int, int> testMap; 
  testMap.max_load_factor(0.75); // can specify max load factor
  std::cout << "Configured max load factor: " << testMap.max_load_factor() << "\n";
  LogMap(testMap);
  for (int i = 0; i < 16; i++){
    testMap.insert({i, i-1});
    LogMap(testMap);
  }

  // can rehash to at least a specified num of buckets
  testMap.rehash(500);
  std::cout << "New bucket count: "<< testMap.bucket_count() << '\n';

  // can reserve space for _ items
  std::unordered_map<int, int> testMap2;
  testMap2.max_load_factor(0.25);
  testMap2.reserve(500); // reserve space for 500 ints
  std::cout << "Bucket count (reserved 500 items, max load 0.25): " << testMap2.bucket_count() << '\n';
  std::cout << "Size of this empty set: " << sizeof(testMap2) << " bytes\n";

}


