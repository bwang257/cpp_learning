/*
C++20 erase algs to simplify remove_erase idiom for stl containers
** this convenience does not come at a cost, behavior is equal to remove-erase idiom **
*/

#include <iostream>
#include <vector>
#include <string>
#include <map>

// to simplify need to first remove, and then erase "zombie data" at the end of the range
// actually defined within #include <vector>, <string>, <list>, <map>, etc.


void PrintVector(const std::vector<int>& Values) {
  for (auto Value : Values) {
    std::cout << Value << ' ';
  }
  std::cout << '\n';
}

void stl_erase(){
  // std::erase, returns num elements removed
  std::vector nums{1, 2, 3, 4, 2, 2, 2, 5, 6, 7};
  size_t removed_count{std::erase(nums, 2)};
  std::cout << "Removed " << removed_count << " 2's from nums\n";
  PrintVector(nums);

  std::string text{"Hi! My name is Brian."};
  std::cout << "Orignal: " << text << "\n";
  size_t removed_count2{std::erase(text, 'a')};
  std::cout << "Modified: " << text << "\n";
  std::cout << "Removed " << removed_count2 << " a's from text\n";
}

void stl_erase_if(){
  // std::erase_if
  // takes in predicate
  std::string text{"hi! my name is brian."};
  std::cout << "Orignal: " << text << "\n";
  size_t removed{std::erase_if(text, [](const char& c){ return c > 100; })}; // 100 is ASCII val of 'd'
  std::cout << "Modified: " << text << "\n";
  std::cout << "Removed " << removed << " letters from text\n";
}

using Scores = std::map<std::string, int>;
void PrintMap(const Scores& s) {
  for (const auto& [Name, Score] : s) {
    std::cout << Name << ": " << Score << '\n';
  }
}

int main(){
  stl_erase();
  std::cout << "\n";
  stl_erase_if();
  std::cout << "\n";

  // example erasing from a map using pairs
  Scores HighScores{
    {"Alice", 1500},
    {"Bob", 99},
    {"Charlie", 1200},
    {"David", 75}
  };

  std::cout << "--- Before ---\n";
  PrintMap(HighScores);

  // Erase if the score (the pair's second element) is < 100
  size_t RemovedCount{std::erase_if(HighScores, [](const auto& item){
    auto const& [name, score] = item; 
    return score < 100;
    })};

  std::cout << "\n--- After ---\n";
  PrintMap(HighScores);
  std::cout << "Removed " << RemovedCount << " entries.\n";
}