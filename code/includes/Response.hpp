#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <sys/dir.h>
#include <unistd.h>

#include <iostream>
#include <map>

#include "../includes/Request.hpp"

class Response {
 private:
  std::string _result;
  std::string _statusLine;
  std::string _header;
  std::string _body;
  std::map<enum MIME, std::string> _mimeTypes;

 public:
  Response(std::string result);
  ~Response();
  void setBody(std::string body);
  void setHeader(std::string header);
  void setStatusLine(std::string statusLine);
  void directoryListing(std::string path);
  std::string getBody();
  std::string getHeader();
  std::string getStatusLine();
  void convertCGI(std::string cgiResult);
  int sendResponse(int clientSocket);
};

#endif
