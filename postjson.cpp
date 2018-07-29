#include <iostream>
#include <cstdlib>
#include <string>
#include <istream>
#include <ostream>
#include <iterator>
#include <curl/curl.h>

int main()
{
  auto status = 0;
  CURL *curl;
  CURLcode res;
  struct curl_slist *headers;
 
  curl = curl_easy_init();

  if(curl) {
    if(std::getenv("VERBOSE")) {
      curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    }

    auto envurl = std::getenv("URL");
    auto url = envurl ? envurl : "http://localhost:11235";

    std::cin >> std::noskipws;
    std::istream_iterator<char> it(std::cin);
    std::istream_iterator<char> end;
    std::string body(it, end); 

    headers = curl_slist_append(headers, "Content-Type: application/json");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
 
    res = curl_easy_perform(curl);

    if(res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
      status = 1;
    }
 
    curl_slist_free_all(headers);
    curl_easy_cleanup(curl);
  }

  return status;
}