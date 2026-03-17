
/*
Implementation of the Johnson-Trotter Algorithm in C++
with a slight modification to find permutations where
pi_i -i = pi_j - j implied i = j.

Note: this is probably not the most efficient approach -
Once the condition has been violated, further permutations
along that "sub-branch" are not necessary

Compile with:
g++ -std=c++20 perm.cpp -o run

Run with:
./run
*/

#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>
#include <ranges>
#include <string>
#include <iomanip>

bool print{false}; // change to print out permutations that satisfy condition
unsigned int num_valid{};

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

int main(){
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
