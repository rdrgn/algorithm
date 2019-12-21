#include <unistd.h>
#include <iostream>
#include <string>

std::string HttpGet(std::string url) {
  FILE *f = popen(("curl -sk \"" + url + "\"").c_str(), "r");
  if (f == nullptr) perror("error");
  char buffer[1024];
  std::string response;
  while (!feof(f)) {
    if (fgets(buffer, 1024, f) == NULL) break;
    response += (std::string)(buffer);
  }
  pclose(f);
  return response;
}

// test
int main() { std::cout << HttpGet("https://www.example.com/") << std::endl; }
