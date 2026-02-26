/*
Regex Capture Groups
*/

#include <iostream>
#include <string>
#include <cassert>
#include <regex>

using namespace std::string_literals;

// denoted by (), uses same rules as we have seen
// ex (hello|goodbye), ([hc]ello), (hel\w)

void greedy_lazy(){
  // repetition quantifies such as *, + are greedy --> can add ? to make them lazy

  // ex. get email provider (gmail)
  std::string email{"example@gmail.co.uk"};
  // greedy: .* captures as much as possible -> "gmail.co"
  std::regex pattern{R"(.*@(.*)\..*)"};
  std::smatch matches;
  if (std::regex_match(email, matches, pattern)){
    std::cout << "Greedy: " << matches[1] << "\n";
  }

  // lazy: .*? captures as little as possible -> "gmail"
  std::regex pattern_lazy{R"(.*@(.*?)\..*)"};
  if (std::regex_match(email, matches, pattern_lazy)){
    std::cout << "Lazy: " << matches[1] << "\n";
  }
  std::cout << "\n";
}

void non_capture_groups(){
  // (?: ) is a non-capturing group; add ? after to make it optional
  std::regex pattern{"The (?:red|brown)? ?fox"};
  std::string input{"The fox"};
  std::string input2{"The brown fox"};

  std::regex pattern2{R"(The (?:(?:red|brown) ){0,2}fox)"};
  std::string input3{"The red brown fox"};

  assert(std::regex_match(input, pattern));
  assert(std::regex_match(input2, pattern));
  assert(std::regex_match(input3, pattern2));
}


void match_results(){

  std::string Input{"Hello World"};
  std::regex Pattern{"Hello (.*)"};
  std::smatch Matches;

  // overload of regex search/match
  if (std::regex_search(Input, Matches, Pattern)) {
    assert(Matches.size() == 2); // # submatches found
    assert(Matches[0] == Input); // first entry is the overall match
    assert(Matches[1] == "World"); // subsequent entries are one for each capture group
    assert(Matches[1].length() == 5); // can access properties such as length
  }
}

void multiple_matches(){
  // we use regex_iterator
  std::string Input{"Hello World, Goodbye World"};
  std::regex Pattern{"(Hello|Goodbye) (World|Everyone)"};
  std::sregex_iterator Iterator{Input.begin(), Input.end(), Pattern};
  std::sregex_iterator End; // need end iterator to compare against

  int match_num{1};
  while (Iterator != End) {
    std::cout << "Match " << match_num++ << ":";
    for (auto Match : *Iterator) {
      std::cout << "\n  Submatch: " << Match;
    }
    std::cout << "\n";
    ++Iterator;
  }
  std::cout << "\n";
}

void token_multi_match(){
  // token iterator skips over intermediate std::mathc_results contianers
  // goes straight to std::sub_match objects
  std::string Input{"Hello World, Goodbye Everyone"};
  std::regex Pattern{"(Hello|Goodbye) (World|Everyone)"};
  assert(Pattern.mark_count() == 2); // count number of capture groups
  
  std::sregex_token_iterator Iterator{Input.begin(), Input.end(), Pattern};
  std::sregex_token_iterator End;

  while (Iterator != End) {
    std::cout << "Submatch: " << (*Iterator) << "\n";
    ++Iterator;
  }

  // can specify which capture group index we want using a single index or vecotr/array/initializer list
  // std::sregex_token_iterator Iterator{Input.begin(), Input.end(), Pattern, 1};
  // std::sregex_token_iterator Iterator{Input.begin(), Input.end(), Pattern, {0,1}};

  std::cout << "\n\n";
}

void replace(){
  // regex_replace, takes in input string, search term, and what to replace the search term
  // with
  std::string input{"email me at brian@gmail.com or brian@yahoo.com"};
  std::regex search{R"(\w*@[\w.]*)"};
  std::string replace{"[redacted]"};

  std::string updated{std::regex_replace(input, search, replace)};

  std::cout << "Before: " << input << "\nAfter: " << updated << "\n";

  // applied to capture groups, we use $i to denote use value captured in capture group i
  // do actual dollar sign with $$ (ex. ("$$3.50"))
  std::string Input{"The name's James Bond"};
  std::regex Search{"(The name's) (.*) (.*)"};
  std::string Replace{"$1 $3, $2 $3"};

  std::string Updated{std::regex_replace(
    Input, Search, Replace)};

  std::cout << "Before: " << Input<< "\n After: " << Updated << "\n";

  // access full substring matched using $7
  std::string Input2{"The hungry brown cat and the sleepy black bear"};
  std::regex Search2{".*?(happy|hungry|sleepy) (brown|black) (bear|fox|cat).*?"};
  std::string Replace2{"Matched: $& \n  Animal: $3\n  Color: $2\n  Mood: $1\n\n"};

  std::cout << std::regex_replace(Input2, Search2, Replace2);

  std::cout << "\n";
}




int main(){
  greedy_lazy();
  non_capture_groups();
  match_results();
  multiple_matches();
  token_multi_match();
  replace();

  std::cout << "All assertions passed\n";
}