/*
Working with http in modern C++
- using alpaca api
- authentication
- sync/async requests
- interceptors
*/

#include <cpr/cpr.h>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include <memory>

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

void alpaca_api(){
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
    return;
  }

  if (response.status_code >= 400){
    std::cerr << "Request failed\n";
    return;
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
  std::cout << "Rate limit reset: " << response.header["X-Ratelimit-Reset"] << " unix time\n\n"; // seconds from 00:00:00 UTC on 1st January 1970
}

void synch_authentication(){
  // treat HTTP communication as regular function call
  // synchronous calls are blocking

  // basic authentication (username, password in header without encryption) api
  cpr::Url URL{"https://www.httpbin.org/basic-auth/brian/secret"}; // brian is username, secret is password
  cpr::Authentication Auth{"brian", "secret", cpr::AuthMode::BASIC}; // need authentication header
  cpr::Response response{cpr::Get(URL, Auth)};
  std::cout << '\n' << response.text << '\n';

  // digest authentication (credentials inserted into header in encrypted form)
  // more of a complex process but is handled by cpr
  cpr::Url URL2{"http://www.httpbin.org/digest-auth/auth/brian/secret"};
  cpr::Authentication Auth2{"brian", "secret", cpr::AuthMode::DIGEST};
  cpr::Response response2{cpr::Get(URL, Auth)};
  std::cout << '\n' << response2.text << '\n';

  // bearer token authentication
  cpr::Url URL3{"http://www.httpbin.org/bearer"};
  cpr::Bearer token{"my-secret-token"};
  cpr::Response response3{cpr::Get(URL3, token)};
  std::cout << response3.text << '\n';
}

void asynch_req(){
  // when request is done, a function is called to handle the completed request
  // this type of function is known as a callback

  cpr::Url URL{"https://www.httpbin.org/basic-auth/brian/secret"};
  cpr::Authentication Auth{"brian", "secret", cpr::AuthMode::BASIC};


  bool run{true};
  auto callback{[&run](const cpr::Response& Res){
    json Doc{json::parse(Res.text)};
    std::cout << "Status code: " <<  Res.status_code << '\n';
    std::cout << "Authenticated: " << Doc.at("authenticated") << '\n';
    std::cout << "Respone was ready after " << Res.elapsed << " seconds\n\n";
    run = false;
  }};

  cpr::GetCallback(callback, URL, Auth);

  // this is not blocked
  std::cout << "Loading...\n";
  while (run){ }
}


void sessions(){
  // sessions are stateful objects to maintain state across multiple requests
  cpr::Session Session;
  Session.SetUrl("http://www.test.com");

  Session.SetParameters({{"first", "one"}, {"second", "two"}});

  cpr::Response Res1{Session.Get()};
  std::cout << "Completed request:\n" << Res1.url << '\n';

  Session.SetParameters({{"third", "three"}});
  cpr::Response Res2{Session.Get()};
  std::cout << "Completed request:\n" << Res2.url << "\n\n";

  // if doing asynch, use shared ptr to maintain lifecycle
}


// interceptors inherit from the cpr::Interceptor class
// can add interceptors to a class, multiple interceptors

// ex implementation
class myInterceptor : public cpr::Interceptor {
  public:
    cpr::Response intercept(cpr::Session& Ses) override {
      std::cout << "Request to " << Ses.GetFullRequestUrl() << " started\n";
      
      cpr::Response Res;
      int num_tries{3};
      while (num_tries > 0){
        Res = proceed(Ses);
        if (Res.status_code >= 400){
          std::cout << "Request failed: " << Res.status_line << '\n';
          --num_tries;
        } else {
          return Res;
        }
      }
      std::cout << "No tries remaining - Mission failed\n"; 
      return Res;
    }
};


void interceptors(){
  // if multiple interceptors (ex. A, B) 
  // --> A is called first, proceed calls B. When the request finishes, B finishes, followed by A
  // cpr manages the process for us
  cpr::Session ses{};
  ses.AddInterceptor(std::make_shared<myInterceptor>());
  ses.SetUrl("http://www.httpbin.org/status/504");
  ses.Get();
}



int main(){
  alpaca_api();
  synch_authentication();
  asynch_req();
  sessions();
  interceptors();
}