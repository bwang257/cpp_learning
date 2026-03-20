/*
JSON in C++ using nlohmann::json

Compile with
g++ -std=c++17 [path to nlohmann] nlohmann_json.cpp -o run
*/

#include <nlohmann/json.hpp>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <string>
#include <cassert>

using json = nlohmann::json;

void basics(){
  std::cout << '\n';

  std::string Data{R"({ "name": "Brian", "role": "Student", 
                        "interests":[{"coding": ["C++", "Python"]}, "math", "running"], 
                        "numbers": [1, 2, 3, 4, 6]})"};
  assert(json::accept(Data)); // check if the string is a valid JSON before trying to parse

  json Doc;
  try {
    Doc = json::parse(Data); // parse string --> json
  } catch (json::parse_error e){
    std::cout << "Parsing failed: " << e.what() << '\n';
    exit(1);
  }

  std::string name{Doc["name"]};
  std::string interest1{Doc["interests"][0]["coding"][0]}; // example of chain of []

  std::cout << name << "\n";
  std::cout << interest1 << '\n';

  // mapping JSON types to C++ types
  // usually able to easily map like std::string (above), int

  auto interest2{Doc["interests"][1].get<std::string>()}; // can explicitly specify type
  std::cout << interest2 << '\n';

  auto numbers{Doc["numbers"].get<std::vector<int>>()};
  for (int i{}; i < numbers.size(); ++i) std::cout << i << ", ";
  std::cout << '\n';

  // if variable already exists
  std::vector<int> Numbers2;
  Doc["numbers"].get_to(Numbers2);

  // to maps
  std::string Data2{R"({"name": "Bob", "role": "student"})"};
  json Doc2{json::parse(Data2)};
  std::map<std::string, std::string> Map;
  Doc2.get_to(Map);

  std::cout << Doc2 << '\n'; // stream entire document
  std::cout << Map["name"] << '\n';
  std::cout << Doc2["role"] << '\n';

  // dump returns current state of the JSON true (or any subpart)
  // accepts optional arg for how many spaces to use for indentation (default is just one line)
  std::cout << Doc.dump(2) << '\n';
  std::cout << '\n';
}

class Stock{
  public:
    Stock() = default;
    Stock(std::string ticker, std::string company) : ticker{ticker}, company{company}{}
    std::string ticker;
    std::string company;
    float price = 205.9;

    // we can use a macro instead of defining to_json/from_json, intrusive if need to access private fields
    // NLOHMANN_DEFINE_TYPE_INTRUSIVE(Stock, ticker, company)
};

void to_json(json& j, const Stock& S){
  j = json{{"ticker", S.ticker}, {"company", S.company}, {"price", S.price}};
}

void from_json(const json& j, Stock& S){
  j.at("ticker").get_to(S.ticker);
  j.at("company").get_to(S.company);
  j.at("price").get_to(S.price);
}

void creating_JSON(){
  json Doc;
  Doc["movie"] = "Star Wars";
  Doc["released"] = true;
  Doc["year"] = 1977;

  // Array
  Doc["cast"] = {"Mark Hamill", "Harrison Ford",
                 "Carrie Fisher"};

  // Object
  Doc["director"] = {{"name", "George Lucas"},
                     {"born", 1944}};

  // Array of Objects
  Doc["similar_movies"] = {
      {{"name", "Dune"}, {"year", 2021}},
      {{"name", "Rogue One"}, {"year", 2016}}};

  std::cout << Doc.dump(2) << "\n\n";

  // can also create a JSON directly using nlohmann::literals
  // (just add _json to end of raw string)
  using namespace nlohmann::literals;
  json Doc2{R"({"name": "Brian"})"_json};
}

void userDefinedTypes(){
  // need to define to_json and from_json functions
  std::string data{R"({"ticker": "AMZN", "company": "Amazon", "price": 100.56})"};
  json Doc{json::parse(data)};

  Stock amzn;
  Doc.get_to(amzn);
  std::cout << amzn.ticker << ": " << amzn.company << '\n';
  
  json Doc2{amzn};
  std::cout << Doc2.dump(2) << '\n';

  // can directly plug in custom types into JSON creation in function above
  // if macros included or needed to/from_json are defined 
}

void JSON_File_IO(){
  std::fstream File;

  // writing to json file
  File.open(R"(./file.json)", std::ios::out | std::ios::trunc);
  json Doc{
      {"movie", "Star Wars"},
      {"released", true},
      {"year", 1977},
      {"cast", {1, 0, 2}},
      {"director",
       {{"name", "George Lucas"},
        {"born", 1944}}},
      {"related_movies",
       {{{"name", "Rogue One"}, {"year", 2016}},
        {{"name", "Dune"}, {"year", 2021}}}}};
  
  File << Doc;
  File.close();

  // reading from json file
  File.open(R"(./file.json)", std::ios::in);
  json Doc2{json::parse(File)};
  std::cout << Doc2.dump(2) << "\n\n";
}

void saving_prog_state(){

  Stock s;

  std::fstream File;
  std::filesystem::directory_entry saveFile{R"(./savefile.json)"};
  if (saveFile.is_regular_file()){
    std::cout << "Loading saved data\n";
    File.open(saveFile, std::ios::in);
    json Data = json::parse(File);
    Data.get_to(s);
  } else {
    std::cout << "Loading new data\n";
    File.open(saveFile, std::ios::out | std::ios::trunc);
    s.ticker = "AAPL";
    s.company = "Apple";
    s.price = 248.24;
    json Data = s;
    File << Data;
  }
  File.close();

  std::cout << s.ticker << ": " << s.price << '\n';
  std::cout << "\n";
}

void JSON_iteration(){
  // can access key and values:
  std::string Data{R"(
    {
      "name": "Roderick",
      "role": "Barbarian",
      "level": 10,
      "guild": {"name": "The Bandits" }
    }
  )"};

  json Doc{json::parse(Data)};
  for (auto it = Doc.begin(); it != Doc.end(); ++it) {
    std::cout << "Key: " << it.key() << ", Value: " << it.value() << '\n';
  }
  
  // can also do for (auto& Item : Doc.items()) ===> Item.key(), Item.value()
  // or structured binding: for (auto& [key, value] : Doc.items())
  // note: all of these methods above are not recursivem
}

void comparing_JSON(){
  // can directly compare using !=, ==
  std::string  Data{R"({"name": "Roderick", "role": "Barbarian"})"};
  std::string Data2{R"({"name": "Roderick", "role": "Barbarian"})"};

  json Doc1{json::parse(Data)};
  json Doc2{json::parse(Data)};

  assert(Doc1 == Doc2);
  Doc1["name"] = "Anna";
  assert(Doc1 != Doc2);
}

int main(){
  basics();
  creating_JSON();
  userDefinedTypes();
  JSON_File_IO();
  saving_prog_state();
  JSON_iteration();
  comparing_JSON();

  /*
  There is also many methods not applied here
  1. Type checkers
    is_number()
    is_number_integer()
    is_array()
    is_primitive()
    is_structured() --> if element is array or object
    .
    .
    .
  2.
    .size() --> num keys for an object or size of array, 1 for str/bool/num, 0 for null/missing keys
    .empty() --> if size is 0
    .contains() --> if a key is present
    .erase() --> removing a key or element from an array
    .clear() --> sets element to default vall
  */
}