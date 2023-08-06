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

  std::map<enum MIME, std::string> _mimeTypes;
  std::map<int, std::string> _statusCodes;

 public:
  Response();
  ~Response();

  void directoryListing(std::string path);
  void convertCGI(std::string cgiResult);
  int sendResponse(int clientSocket);

  std::string getStatusCode(int key);
  void setErrorRes(int statusCode);
  void setResult(const std::string &statusLine, const std::string &header,
                 const std::string &body);
  const std::string &getResult();
};

#endif
