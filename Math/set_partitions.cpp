/*
Exploration of set partition concepts in C++

Compile with:
g++ set_partitions.cpp -o run
*/

#include <iostream>
#include <sstream>
#include <vector>

void print_rg(const std::vector<int>& rg){
  for (int i{}; i < rg.size(); ++i){
    std::cout << rg[i];
  }
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
    std::cout << '\n';
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

// d_m,t is the number of ways of finishing the last
// m positions if t is the max of the first n-m positions
size_t d(int m, int t, std::vector<std::vector<size_t>>& cache){
  if (m == 1) return t+1;
  if (m == 0) return 1; // one way to do nothing
  if (cache[m][t]  != SIZE_MAX) return cache[m][t];
  return cache[m][t] = t*d(m-1, t, cache) + d(m-1, t+1, cache);
}

// finds the rank of a RG functions
size_t rank_rg(const std::vector<int>& v){
  int n = v.size();
  std::vector<int> u(n); // trailing max
  u[0] = 1;

  // get trailing maxes
  for (int i{1}; i < n; ++i){
    u[i] = std::max(u[i-1], v[i-1]);
  }

  size_t rank{};
  std::vector<std::vector<size_t>> cache(n+1, std::vector<size_t>(n+1, SIZE_MAX));
  for (int i{n-1}; i >= 0; --i){
    int t = u[i];
    rank += d(n-i-1, t, cache) * (v[i]-1);
  }
  return rank; 
}

void interactive_rg_lex_list(){
  std::cout << "\n=== RG Lex Order List ==\n";
  int n;
  std::cout << "Enter n: ";
  std::cin >> n;
  std::cin.ignore();

  list_rg_lex(n);
}

void interactive_rank_rg(){
  std::cout << "\n=== RG Rank Lex Order ==\n";

  std::string input;
  std::cout << "Enter desired RG function with commas between entries (ex: \"1, 1, 3, 2\"):\n";
  std::getline(std::cin, input);
  std::stringstream ss{input};

  std::string val;
  std::vector<int> v;

  while (std::getline(ss, val, ',')){
    int entry = std::stoi(val);
    v.push_back(entry);
  }

  std::cout << "The rank of "; 
  print_rg(v);
  std::cout << " is " << rank_rg(v) << '\n';
}

int main(){
  interactive_rg_lex_list();
  interactive_rank_rg();
}