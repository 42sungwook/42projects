#ifndef CGI_HPP
#define CGI_HPP

#include <unistd.h>

#include <iostream>
#include <map>
#include <string>

class Cgi {
 private:
  char** _envp;
  std::string _res;
  std::map<std::string, std::string> _env;
  std::string _cgiPath;

  std::string makeRet();
  void makeEnv(std::map<std::string, std::string> param);

 public:
  Cgi();
  ~Cgi();

  void reqToEnvp(std::map<std::string, std::string> param);
  void excute();
  std::string getRet();
};

#endif