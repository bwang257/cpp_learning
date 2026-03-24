/*
Exploration of Integer Partitions using C++

Compile with:
g++ -std=c++23 int_partitions.cpp -o run
*/

#include <iostream>
#include <vector>
#include <string>
#include <ranges>
#include <numeric>
#include <sstream>

const std::vector<std::string> super_scripts = {"\u2070", "\u00B9", "\u00B2", "\u00B3", "\u2074", "\u2075", "\u2076", "\u2077", "\u2078", "\u2079"};

// print partition given vals and their multiplicities
void print_partition(const std::vector<int>& p, const std::vector<int>& m, int idx){
  // prints partition using unicode superscripts
  for (auto&& [val, mult] : std::views::zip(p, m) | std::views::take(idx + 1)){
    std::string mult_s{std::to_string(mult)};
    std::string exp{""};
    for (const char& c : mult_s){
      exp += super_scripts[c - '0'];
    }
    std::cout << val << exp << ' ';
  }
  std::cout << '\n';
}

// print partition given partition with repeated vals
void print_partition(const std::vector<int>& lambda){
  int curr_count{1};
  int curr_val = lambda[0];
  for (int idx{1}; idx < lambda.size(); ){
    while (idx < lambda.size() && lambda[idx] == curr_val){
      ++curr_count;
      ++idx;
    }

    std::string cnt_s{std::to_string(curr_count)};
    std::string exp{""};
    for (const char& c : cnt_s){
      exp += super_scripts[c - '0'];
    }
    std::cout << curr_val << exp << ' ';

    if (idx < lambda.size()) curr_val = lambda[idx];
    curr_count = 0;
  }
  std::cout << '\n';
}

// helper function for finding rank of a desired parititon for
// brute force algorithm below
int rank{0};
bool found{false};
void check_partition(const std::vector<int>& p, const std::vector<int>& p_exp, const std::vector<int>& m, const std::vector<int>& m_exp, int idx){
  ++rank;
  int len = (int)p_exp.size();
  if (idx + 1 == len &&
      std::equal(p.begin(), p.begin() + len, p_exp.begin()) &&
      std::equal(m.begin(), m.begin() + len, m_exp.begin())){
    found = true;
    std::cout << "Rank: " << rank << '\n';
  }
}

// listing integer partitions in reverse lex order
void rev_lex_list(int n){
  std::vector<int> p(n, 0), m(n, 0);
  p[0] = n; 
  m[0] = 1;
  int idx = 0;
  bool Done{false};
  while (!Done){
    print_partition(p, m, idx);

    if (p[idx] > 1 || idx > 0){
      int s, k, w, u, v, k1;  
      if (p[idx] == 1){
        s = p[idx-1] + m[idx];
        k = idx - 1;
      } else {
        s = p[idx];
        k = idx;
      }
      w = p[k]-1;
      u = s/w; 
      v = s % w;
      m[k] = m[k]-1;
      if (m[k] == 0) k1 = k;
      else k1 = k+1;
      m[k1] = u;
      p[k1] = w;
      if (v==0) idx = k1;
      else {
        m[k1+1]=1;
        p[k1+1] = v;
        idx = k1+1;
      }
    } else {
      Done = true;
    }
  }
}

// brute force ranking for algorithm above
void rank_rev_lex_brute(int n, const std::vector<int>& p_exp, const std::vector<int>& m_exp){
  std::vector<int> p(n, 0), m(n, 0);
  p[0] = n;
  m[0] = 1;
  int idx = 0;
  bool Done{false};
  while (!Done){
    check_partition(p, p_exp, m, m_exp, idx);
    if (found) break;
    if (p[idx] > 1 || idx > 0){
      int s, k, w, u, v, k1;  
      if (p[idx] == 1){
        s = p[idx-1] + m[idx];
        k = idx - 1;
      } else {
        s = p[idx];
        k = idx;
      }
      w = p[k]-1;
      u = s/w; 
      v = s % w;
      m[k] = m[k]-1;
      if (m[k] == 0) k1 = k;
      else k1 = k+1;
      m[k1] = u;
      p[k1] = w;
      if (v==0) idx = k1;
      else {
        m[k1+1]=1;
        p[k1+1] = v;
        idx = k1+1;
      }
    } else {
      Done = true;
    }
  }
}

// p(n,k) gives number of partitions of n where largest part is less than k
size_t p(int n, int k, std::vector<std::vector<int>>& cache){
  if (n == 0) return 1;
  if (n < 0) return 0;
  if (k == 1) return 0;
  if (cache[n][k] != -1) return cache[n][k];
  cache[n][k] = p(n, k-1, cache) + p(n-(k-1), k, cache);
  return cache[n][k]; 
}

// instead of removing elements from lamda, simply shift the index
size_t S(const std::vector<int>& lambda, int idx, int n, std::vector<std::vector<int>>& cache){
  if (idx == lambda.size()) return 0;
  return p(n, lambda[idx], cache) +  S(lambda, idx+1, n-lambda[idx], cache);
}

// rank partition of n in reverse lex order
size_t Rank(std::vector<int> lambda, int n){
  std::vector<std::vector<int>> pcache(n+1, std::vector<int>(n+2, -1)); 
  return p(n, n+1, pcache)  - S(lambda, 0, n, pcache);
}

// unrank a rank to get the partition for n
std::vector<int> unrank(size_t rank, int n){
  std::vector<std::vector<int>> pcache(n+1, std::vector<int>(n+2, -1)); 
  std::vector<int> lambda;
  int S = p(n, n+1, pcache) - rank;
  while (n > 0){
    if (S == 0){
      lambda.push_back(1);
      --n;
    } else {
      int lam = 2;
      int k;
      while (p(n, lam, pcache) <= S){
        lam++;
      }
      lambda.push_back(--lam);
      S -= p(n, lam, pcache);
      n -= lam;
    }
  }
  return lambda;
}

// overload of unrank with a cache passed to it
std::vector<int> unrank(size_t rank, int n, std::vector<std::vector<int>> pcache){
  std::vector<int> lambda;
  int S = p(n, n+1, pcache) - rank;
  while (n > 0){
    if (S == 0){
      lambda.push_back(1);
      --n;
    } else {
      int lam = 2;
      int k;
      while (p(n, lam, pcache) <= S){
        lam++;
      }
      lambda.push_back(--lam);
      S -= p(n, lam, pcache);
      n -= lam;
    }
  }
  return lambda;
}

void interactive_rev_lex_list(){
  int n;
  std::cout << "Enter n: ";
  std::cin >> n;
  std::cin.ignore();

  rev_lex_list(n);
}

void interactive_brute_lex_rank(){
  std::string input;
  std::cout << "Enter desired vector p with commas between entries (ex: \"4,4,3,1\"):\n";
  std::getline(std::cin, input);
  std::stringstream ss{input};

  std::string val;
  std::vector<int> p_exp;

  while (std::getline(ss, val, ',')){
    int entry = std::stoi(val);
    p_exp.push_back(entry);
  }

  std::cout << "Enter desired vector m with commas between entries (ex: \"4,4,3,1\"):\n";
  std::getline(std::cin, input);
  std::stringstream ss2{input};

  std::vector<int> m_exp;

  while (std::getline(ss2, val, ',')){
    int entry = std::stoi(val);
    m_exp.push_back(entry);
  }

  if (p_exp.size() != m_exp.size()){
    std::cerr << "Expected p and m vectors are different sizes\n";
    exit(1);
  }
  int n{};
  for (int i{}; i < p_exp.size(); ++i){
    n += (p_exp[i] * m_exp[i]);
  }
  rank_rev_lex_brute(n, p_exp, m_exp);
}

void interactive_lex_rank(){
  std::string input;
  std::cout << "Enter desired lambda with commas between entries (ex: \"4,4,3,1\"):\n";
  std::getline(std::cin, input);
  std::stringstream ss{input};

  std::string val;
  std::vector<int> lambda;

  while (std::getline(ss, val, ',')){
    int entry = std::stoi(val);
    lambda.push_back(entry);
  }

  int n = std::accumulate(lambda.begin(), lambda.end(), 0);
  std::cout << "Rank: " <<  Rank(lambda, n) << '\n';
}

void interactive_lex_unrank(){
  int n;
  int rank;

  std::cout << "Enter n: ";
  std::cin >> n;
  std::cin.ignore();

  std::cout << "Enter rank: ";
  std::cin >> rank;
  std::cin.ignore();

  std::vector<std::vector<int>> pcache(n+1, std::vector<int>(n+2, -1)); 
  if (rank < 0 || rank > p(n, n+1, pcache)){
    std::cerr << "Invalid rank\n";
    exit(1);
  }

  auto lambda = unrank(rank, n, pcache);
  print_partition(lambda);
}

int main(){
  // interactive_rev_lex_list();
  // interactive_brute_lex_rank();
  // interactive_lex_rank();
  interactive_lex_unrank();
}