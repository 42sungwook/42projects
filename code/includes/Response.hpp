#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <unistd.h>

#include <iostream>
#include <map>

class Response {
 private:
  std::string _result;
  std::string _statusLine;
  std::string _header;
  std::string _body;

 public:
  Response(std::string result);
  ~Response();
  void setBody(std::string body);
  void setHeader(std::string header);
  void setStatusLine(std::string statusLine);
  std::string getBody();
  std::string getHeader();
  std::string getStatusLine();
  void convertCGI(std::string cgiResult);
  int sendResponse(int clientSocket);
};

#endif