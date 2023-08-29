#ifndef CGI_HPP
#define CGI_HPP

#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "ErrorException.hpp"
#include "Utils.hpp"
#include "Kqueue.hpp"

class Cgi {
 private:
  char** _envp;
  std::string _res;  // cgi가 보내주는 response
  std::map<std::string, std::string> _env;

  // header parsing data를 받아서 _env 생성
  void makeEnv(std::map<std::string, std::string> param);
  std::string mkTemp();

 public:
  Cgi();
  ~Cgi();

  // client's request를 받아서 execve에 사용할 _envp를 생성
  void reqToEnvp(std::map<std::string, std::string> param);
  // _envp, body(parsing)를 받아서 cgi를 실행
  void execute(const std::string& body, Kqueue &kq, int clientFd);
  const std::string &getRes() const;
};

#endif
