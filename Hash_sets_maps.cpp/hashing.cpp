/*
Introduction to hashing in C++
*/

#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>


// hash functions should map two equal objects to the same value
struct User{
  std::string Email;
  // override to determine if two objects are the same in case of collision
  bool operator==(const User& Other) const{
    return Email == Other.Email;
  }
};

namespace std {
template<>
struct hash<User>{
  size_t operator()(const User& U) const {
    return std::hash<std::string>{}(U.Email);
  }
};
}



int main() {
  // secondary chaining implmented in std::unordered_multiset/map
  // multiple values mapped to a single key

  std::unordered_multimap<int, std::string> grades;
  grades.insert({101, "Math"});
  grades.insert({101, "Science"});
  grades.insert({102, "History"});

  auto range = grades.equal_range(101);
  std::cout << "101: ";
  for (auto it = range.first; it != range.second; ++it) {
    std::cout << it->second << ", ";
  }
  std::cout << std::endl;

  // load factor is num slots occupied
  // if too high collisions frequent. we can resize but 
  // also need to update has function (ex hash % 20 --> hash % 40) and move all items

  // std::hash, overloads () operator, giving us function-like interface
  // objects that can be used like this known as function object or functor
  auto IntHasher{std::hash<int>{}};
  auto StringHasher{std::hash<std::string>{}};

  std::cout << "\nHashes:\n";
  std::cout << "42: " << IntHasher(42) << '\n';
  std::cout << "'Hello': " << StringHasher("Hello") << '\n';

  // using custom type
  std::unordered_set<User> Users;
  Users.emplace("user@gmail.com");
  User NewUser{"user@gmail.com"};
  if (Users.contains(NewUser)){ // contains is C++20g
    std::cout << "User with email user@gmail.com already added to set\n";
  }

}

