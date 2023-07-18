#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <map>

enum METHOD { GET, POST, DELETE };
enum PROCESS { ERROR, CGI, NORMAL };

class Request {
 private:
  std::string _msg;
  std::map < std::string, int _method;

  int _process;
  std::map<std::string, std::string> _header;
  std::string _body;

 public:
  Request();
  ~Request();
  void parsing(std::string tmp);
  const std::string getMessage() const;
  enum PROCESS getProcess();
  enum METHOD getMethod();
};

#endif