#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <unistd.h>

#include <iostream>
#include <map>

class Response {
 private:
  std::string _result;

 public:
  Response(std::string result);
  ~Response();

  void convertCGI(std::string cgiResult);
  int sendResponse(int clientSocket);
};

#endif