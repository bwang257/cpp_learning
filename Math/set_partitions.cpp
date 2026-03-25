/*
Exploration of set partition concepts in C++

Compile with:
g++ set_partitions.cpp -o run
*/

#include <iostream>
#include <vector>

void print_rg(const std::vector<int>& rg){
  for (int i{}; i < rg.size(); ++i){
    std::cout << rg[i];
  }
  std::cout << '\n';
}

// lists restricted restricted growth (RG) functions on [n]
void list_rg_lex(int n){
  std::cout << "\nRestricted growth function on [" << n << "]:\n";

  std::vector<int> rg(n,1);
  std::vector<int> m(n, 2); // "legal" max for each val of rg
  m[0]= 1;

  bool Done{false};
  int cnt{};
  while (!Done){
    print_rg(rg);
    ++cnt;

    int j{n};
    do {
      --j;
    } while (j >= 0 && rg[j] == m[j]);

    if (j >= 0){
      ++rg[j];
      int new_max = m[j];
      for (int i{j+1}; i < n; ++i){
        rg[i] = 1;
        if (rg[j] == new_max) m[i] = new_max+1;
        else m[i] = new_max;
      }
    } else {
      Done = true;
    }
  }
  std::cout << "\nTotal RG functions: " << cnt << '\n';
}

int main(){
  list_rg_lex(4);
}