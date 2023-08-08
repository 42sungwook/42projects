#ifndef RESPONSE_HPP
#define RESPONSE_HPP

#include <sys/dir.h>
#include <unistd.h>

#include <iostream>
#include <map>

#include "../includes/Request.hpp"
#include "../includes/Utils.hpp"

class Response {
 private:
  std::string _result;
  std::map<std::string, std::string> _headers;
  std::string _body;
  std::string _statusLine;

  std::map<enum MIME, std::string> _mimeTypes;
  std::map<int, std::string> _statusCodes;

 public:
  Response();
  ~Response();

  void directoryListing(std::string path);
  void convertCGI(const std::string &cgiResult);
  int sendResponse(int clientSocket);

  void setErrorRes(int statusCode);
  void setResult();
  void setStatusLine(int code);
  void setHeaders(const std::string &key, const std::string &value);
  void setBody(const std::string &body);
};

#endif
