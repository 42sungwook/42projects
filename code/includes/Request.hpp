#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <map>
#include <sstream>

#include "RootBlock.hpp"

enum METHOD { GET, POST, DELETE };
enum PROCESS { CGI, NORMAL };

class Request {
 private:
  std::map<std::string, std::string> _header;
  std::string _body;
  std::string _host;
  int _port;
  int _error;

 public:
  Request();
  ~Request();
  void parsing(const std::string &raw);
  const std::string getHost();
  const int &getPort();
  const std::string getUri();
  const std::string getMessage() const;
  const int &getError() const;
  enum PROCESS getProcess();
  enum METHOD getMethod();
};

#endif