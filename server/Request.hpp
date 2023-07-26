#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <map>
#include <sstream>

enum METHOD { GET, POST, DELETE };
enum PROCESS { CGI, NORMAL };

class Request {
 private:
  std::map<std::string, std::string> _header;
  std::string _body;
  int _error;

 public:
  Request();
  ~Request();
  void parsing(const std::string& raw);
  const std::string getMessage() const;
  const int& getError() const;
  enum PROCESS checkProcess();
  enum METHOD getMethod();
};

#endif