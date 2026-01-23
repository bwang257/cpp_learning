/*
Projection Functions
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <format>

// when using an algorithm that acts on the items in a collection, we
// often don't want the exact values in the collection be the input

// projection functions receive objects within the collection as a parameter
// returns a new object based on that parameter

// we can implement a comparison function in the algorithm to do this
// but its specific to that algorithm and is a technique that we can't always use
// should be able to use across all algos that accept a projection func

class Fruit{
  public: 
    Fruit(std::string name, int size): name{name}, size{size} {};
    std::string name; 
    int size;
};

// projection function example
int getFruitSize(Fruit f){
  return f.size;
}

void logFruitBowl(std::vector<Fruit> fbowl){
  for (const Fruit& f : fbowl){
    std::cout << std::format("{} of size {}, ", f.name, f.size);
  }
  std::cout << "\n";
}

int main(){
  std::vector<Fruit> fruitBowl;
  fruitBowl.emplace_back("Apple", 3);
  fruitBowl.emplace_back("Banana", 6);
  fruitBowl.emplace_back("Pineapple", 4);
  fruitBowl.emplace_back("Bluberry", 1);

  std::cout << "Sorted by size:\n";
  std::ranges::sort(fruitBowl, {}, getFruitSize);
  logFruitBowl(fruitBowl);

  // can also do this as a projection function
  std::cout << "\nSorted by name:\n";
  std::ranges::sort(fruitBowl, {}, &Fruit::name);
  logFruitBowl(fruitBowl);
}