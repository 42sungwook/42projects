#ifndef CGI_HPP
#define CGI_HPP

#include <unistd.h>

#include <iostream>
#include <map>
#include <sstream>
#include <string>

class Cgi {
 private:
  char** _envp;
  std::string _res;  // cgi가 보내주는 response
  std::map<std::string, std::string> _env;

  // header parsing data를 받아서 _env 생성
  void makeEnv(std::map<std::string, std::string> param);

 public:
  Cgi();
  ~Cgi();

  // client's request를 받아서 execve에 사용할 _envp를 생성
  void reqToEnvp(std::map<std::string, std::string> param);
  // _envp, body(parsing)를 받아서 cgi를 실행
  void excute(const std::string& body);
  std::string& getRes();
};

#endif
