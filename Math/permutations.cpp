
/*
Exploration Permutations in C++
- Johnson Trotter Algorithm to list all permutations
  - Rank/Unrank Algorithms for JT permutations
- listing k element permutations in lex order

Compile with:
g++ -std=c++20 permutations.cpp -o run

Run with:
./run
*/

#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <ranges>
#include <string>
#include <iomanip>
#include <ranges>
#include <algorithm>
#include <sstream>
#include <numeric>
#include <cassert>

size_t factorial(unsigned int n){
  if (n == 2) return n;
  if (n==1 || n== 0) return 1;
  return n * factorial(n-1);
}

bool print{false}; // change to print out permutations that satisfy condition
unsigned int num_valid{};

/*
Note: this is probably not the most efficient approach -
Once the condition has been violated, further permutations
along that "sub-branch" are not necessary
*/
void check_print(const std::vector<int>& pi, int n){
  std::unordered_set<int> distinct;
  for (int i{1}; i <= n; ++i){
    int val = pi[i] - i;
    int mod = ((val % n) + n) % n; // computing mathematical mod

    if (distinct.count(mod)) break;
    distinct.insert(mod);
  }

  if (distinct.size() == n){
    if (print){
      for (const auto& pi_i : pi) std::cout << pi_i << " ";
      std::cout << '\n';
    }
    ++num_valid;
  }
}

/*
Implementation of the Johnson-Trotter Algorithm in C++
with a slight modification to find permutations where
pi_i -i = pi_j - j implies i = j.
*/
void JohnsonTrotter(int n){
  std::vector<int> pi(n+2);
  std::vector<int> pi_inv(n+2);
  std::vector<int> d(n+2);
  std::set<int> A; 

  for (int i{1}; i <= n+1; ++i){
    pi[i] = i;
    pi_inv[i] = i;
    d[i] = -1;
  }
  pi[0] = n+1;
  for (int i{2}; i <= n; i++) A.insert(i);

  bool done{false};
  while (!done){
    check_print(pi, n);
    if (!A.empty()){
      int m = *A.rbegin();
      int j = pi_inv[m];
      pi[j] = pi[j + d[m]];
      pi[j+d[m]] = m;
      pi_inv[m] = pi_inv[m]+d[m];
      pi_inv[pi[j]]=j;
      if (m < pi[j+2*d[m]]){
        d[m] = -d[m];
        A.erase(m);
      }
      for (int i{m+1}; i <= n; ++i) A.insert(i);
    }
    else {
      done = true;
    }
  }
}

size_t JT_Rank(std::vector<int>& pi){

  bool sorted{true};
  int sorted_val{1};
  int max = pi.size();
  int max_idx{-1};

  // preprocess
  for (int i{}; i < max; ++i){
    int val = pi[i];
    if (sorted){
      if (val == sorted_val) ++sorted_val;
      else sorted = false;
    }
    if (val == max) max_idx = i; 
    if (!sorted && max_idx != -1) break;
  }
  ++max_idx; // the JT Rank formula counts indices from 1

  if (sorted) return 0;
  std::erase(pi, pi.size()); // remove max

  size_t prev_rank = JT_Rank(pi);
  return (prev_rank % 2 == 0) ? (max * prev_rank + (max - max_idx)) : (max * prev_rank + (max_idx-1));
}

std::vector<int> JT_Unrank(size_t M, int n){
  std::vector<int> pi(n, 0);
  int k; 
  int dir;
  for (int j{n}; j >= 1; --j){
    int R = static_cast<int>(M % j);
    M /= j;

    if (M % 2 == 1){
      k = -1;
      dir = 1; 
    } else {
      k = n;
      dir = -1;
    }
    int C{0};
    do {
      k += dir;
      if (pi[k] == 0) C+=1;
    } while (C < R+1);
    pi[k] = j;

  }
  return pi;
}

void print_perm(const std::vector<int> perm){
  for (const auto& val : perm) std::cout << val << ", ";
  std::cout << '\n';
}

size_t total_kperms{};

void lexlist_perms(std::vector<int> curr_set, std::vector<int> curr_perm, int k){
  if (curr_perm.size() == k){
    print_perm(curr_perm);
    total_kperms++;
    return;
  }
  for (int x{}; x < curr_set.size(); ++x){
    curr_perm.push_back(curr_set[x]);
    std::vector<int> next_set;
    for (int i{}; i < curr_set.size(); ++i){
      if (x != i) next_set.push_back(curr_set[i]);
    }
    lexlist_perms(next_set, curr_perm, k);
    curr_perm.pop_back();
  }
}

void interactive_JT(){
  std::cout << "=== Johnson-Trotter ===\n";
  std::cout << "\nSelect an option (a/b):\n";
  std::cout << "a) Find valid permutations for a specific n\n";
  std::cout << "b) Find valid permutations from n=1 to user-entered value\n\n";

  std::string input;
  std::cin >> input;
  if (input == "a"){
    int n;
    std::cout << "Enter n: ";
    std::cin >> n;
    JohnsonTrotter(n);
    std::cout << "Valid permutations: " << num_valid << "\n";

  } else if (input == "b"){
    int n;
    std::cout << "Enter max n: ";
    std::cin >> n;
    for (int i : std::views::iota(1, n)){
      JohnsonTrotter(i);
      std::cout << "n = " << std::setw(3) << i << " : " << num_valid << '\n';
      num_valid = 0; // reset counter each time
    }
  } else {
    std::cout << "Entered option invalid.\n";
  }
  std::cout << "\n";
}

void interactive_JT_Rank(){
  std::cout << "=== Johnson-Trotter Rank ===\n";
  int n;
  size_t rank;
  std::cout << "Enter n: ";
  std::cin >> n;
  std::cin.ignore(); // std::cin keeps the \n in input buffer

  std::string input;
  std::cout << "Enter permutation with commas between entries (ex: \"1,2,3,4\"):\n";
  std::getline(std::cin, input);
  std::stringstream ss{input};

  std::string val; 
  std::vector<int> pi;
  std::unordered_set<int> used_entries;

  while (std::getline(ss, val, ',')){
    int entry = std::stoi(val);
    if (used_entries.count(entry)){
      std::cerr << "Not a valid permutation\n";
      exit(1);
    }
    used_entries.insert(entry);
    pi.push_back(entry);
  }

  if (pi.size() != n){
    std::cerr << "Not a valid permutation\n";
  }
  
  std::cout << "Rank: " << JT_Rank(pi) << "\n\n";
}

void interactive_JT_Unrank(){
  std::cout << "=== Johnson-Trotter Unrank ===\n";
  int n;
  std::cout << "Enter n: ";
  std::cin >> n;
  std::cin.ignore();
  
  size_t M;
  std::cout << "Enter rank: ";
  std::cin >> M;

  // bounds checking for rank
  size_t n_fact{factorial(n)};
  if (M < 0 ||  M > n_fact - 1){
    std::cout << "Rank not valid\n";
    exit(1);
  } 
  
  std::vector<int> pi = JT_Unrank(M, n);
  std::cout << "pi: ";
  for (const int& x: pi) std::cout << x << ", ";
  std::cout << "\n\n";
}

void interactive_lexlist_perms(){
  int n;
  std::cout << "Enter n: ";
  std::cin >> n;
  std::cin.ignore();

  int k;
  std::cout << "Enter k: ";
  std::cin >> k;
  
  if (k > n){
    std::cerr << "k must be less than or equal to n\n";
    exit(1);
  }

  std::vector<int> curr_set(n);
  std::iota(curr_set.begin(), curr_set.end(), 1);
  lexlist_perms(curr_set, {}, k);
  assert(total_kperms == factorial(n) / factorial(n-k)); // ensure that there was actually n!/(n-k)! total k-element permutations printed
}


int main(){
  interactive_JT();
  interactive_JT_Rank();
  interactive_JT_Unrank();
  interactive_lexlist_perms();
}
