#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <string.h>
#include <sys/dir.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <map>

#include "../includes/Request.hpp"
#include "../includes/Utils.hpp"

class Response {
 private:
  std::map<std::string, std::string> _headers;
  char *_body;
  std::string _statusLine;

  std::map<int, std::string> _statusCodes;

 public:
  char *_result;
  Response();
  ~Response();

  void directoryListing(std::string path);
  void convertCGI(const char *cgiResult);
  int sendResponse(int clientSocket);

  bool isInHeader(const std::string &key);

  const char *getBody() const;
  void setRedirectRes(int statusCode);
  void setErrorRes(int statusCode);
  void setResult();
  void setStatusLine(int code);
  void setHeaders(const std::string &key, const std::string &value);
  void setBody(const char *body);
};

#endif