/*
Exploration if Integer Partitions using C++

Compile with:
g++ -std=c++23 int_partitions.cpp -o run
*/

#include <iostream>
#include <vector>
#include <string>
#include <ranges>

const std::vector<std::string> super_scripts = {"\u2070", "\u00B9", "\u00B2", "\u00B3", "\u2074", "\u2075", "\u2076", "\u2077", "\u2078", "\u2079"};

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

int main(){
  int n;
  std::cout << "Enter n: ";
  std::cin >> n;
  rev_lex_list(n);
}