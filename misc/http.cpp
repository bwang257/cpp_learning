/*
Working with http in modern C++
- using alpaca api
*/

#include <cpr/cpr.h>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <nlohmann/json.hpp>

using std::string;
using json = nlohmann::json;

// helper for loading in API keys
std::unordered_map<string, string> load_env(const std::string& path){
  std::unordered_map<string, string> env;
  std::ifstream file(path);
  std::string line;

  while (std::getline(file, line)){
    if (line.empty() || line[0] == '#') continue;
    auto delim = line.find('=');
    if (delim == std::string::npos) continue;
    std::string key = line.substr(0, delim);
    std::string val = line.substr(delim+1);
    env[key] = val;
  }

  return env;
}


int main(){
  auto env = load_env("./.env");
  cpr::Url URL{"https://data.alpaca.markets/v2/stocks/bars"};
  cpr::Parameters params{
        {"symbols",    "AAPL"},
        {"timeframe",  "1Hour"},
        {"start",      "2026-01-02T09:30:00Z"},
        {"end",        "2026-01-02T16:00:00Z"},
        {"limit",      "1000"},
        {"adjustment", "raw"},
        {"feed",       "sip"},
        {"sort",       "asc"}
  };

  cpr::Header header{ 
      {"accept",              "application/json"}, // application/json is a content type just like image/jpeg
      {"APCA-API-KEY-ID",     env.at("APCA-API-KEY-ID")},
      {"APCA-API-SECRET-KEY", env.at("APCA-API-SECRET-KEY")}
  };
  // cpr::Body used to provide data (ex. post request)

  // note that the equivalent url is: https://data.alpaca.markets/v2/stocks/bars?symbols=AAPL&timeframe=1Hour&start=2026-01-02T09%3A30%3A00Z&end=2026-01-02T16%3A00%3A00Z&limit=1000&adjustment=raw&feed=sip&sort=asc

  cpr::Response response{cpr::Get(URL, params, header)}; // GET can take args in any order
  std::cout << "Response status code: " << response.status_code << '\n';
  std::cout << "Response status line: " << response.status_line << '\n'; //provides some additional info
  if (response.status_code  == 0){
    std::cerr << "Network error: " << response.error.message << '\n';
    return 1;
  }

  if (response.status_code >= 400){
    std::cerr << "Request failed\n";
    return 1;
  }



  json data{json::parse(response.text)}; // .text gives std::string
  std::cout << "JSON:\n" << data.dump(2) << "\n\n";

  std::cout << "=== Data ===\n";
  for (const auto& [symbol, bars] : data["bars"].items()){
    std::vector<double> closes;
    std::cout << symbol << " closes:\n";
    for (const auto& bar : bars){
      std::cout <<  bar["t"].get<std::string>() << ": " << bar["c"].get<double>() << '\n';
    }
    std::cout << '\n';
  }

  // returned response also has header with supplemental metadata
  // for (auto& Header : response.header){
  //   std::cout << Header.first << ": " << Header.second << '\n';
  // }

  // custom headers added to http specification headers start with X-
  std::cout << "Rate limit remaining: " << response.header["X-Ratelimit-Remaining"] << " requests\n";
  std::cout << "Rate limit reset: " << response.header["X-Ratelimit-Reset"] << " unix time\n"; // seconds from 00:00:00 UTC on 1st January 1970

}