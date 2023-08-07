#include "../includes/Cgi.hpp"

Cgi::Cgi() {}

Cgi::~Cgi() {}

void Cgi::makeEnv(std::map<std::string, std::string> param) {
  _env["AUTH_TYPE"] = param["Authorization"];
  _env["CONTENT_LENGTH"] = param["Content-Length"];
  _env["CONTENT_TYPE"] = param["Content-Type"];
  _env["GATEWAY_INTERFACE"] = "CGI/1.1";
  _env["PATH_INFO"] = param["BasicURI"];
  _env["PATH_TRANSLATED"] = param["RootDir"] + param["BasicURI"];
  _env["QUERY_STRING"] =
      param["URI"].substr(param["URI"].find("?") + 1, std::string::npos);
  _env["REMOTE_ADDR"] = param["ClientIP"];
  _env["REMOTE_IDENT"] = "";
  _env["REMOTE_USER"] = "";
  _env["REQUEST_METHOD"] = param["Method"];
  _env["REQUEST_URI"] = param["URI"];
  _env["SCRIPT_NAME"] = param["URI"].substr(0, param["URI"].find("?"));
  _env["SERVER_NAME"] = param["Name"];
  _env["SERVER_PORT"] = param["Port"]; 
  _env["SERVER_PROTOCOL"] = "HTTP/1.1";
  _env["SERVER_SOFTWARE"] = "Webserv/1.0";
  _cgiPath = param["Cgi-Path"];  // 만들기 보너스 (multi cgi) 포함됨
}

void Cgi::reqToEnvp(std::map<std::string, std::string> param) {
  makeEnv(param);
  _envp = new char *[_env.size() + 1];
  int i = 0;
  for (std::map<std::string, std::string>::iterator it = _env.begin();
       it != _env.end(); it++) {
    _envp[i] = new char[it->first.size() + it->second.size() + 2];
    std::string tmp = it->first + "=" + it->second;
    std::copy(tmp.begin(), tmp.end(), _envp[i]);
    _envp[i][tmp.size()] = '\0';
    i++;
  }
  _envp[i] = NULL;
}

std::string &Cgi::getRes() { return _res; }

void Cgi::excute(const std::string &body) {
  pid_t pid;
  int fd[2];
  int status;
  char buf[1024];
  std::string tmp;

  if (pipe(fd) < 0) {
    std::cerr << "pipe error" << std::endl;
    return;
  }
  if ((pid = fork()) < 0) {
    std::cerr << "fork error" << std::endl;
    return;
  } else if (pid == 0) {
    int rd[2];
    if (pipe(rd) < 0) {
      std::cerr << "pipe error" << std::endl;
      return;
    }
    write(rd[1], body.c_str(), body.size());
    close(rd[1]);
    dup2(rd[0], 0);
    close(fd[0]);
    dup2(fd[1], 1);
    close(fd[1]);
    const char *argv[2] = {_env["PATH_TRANSLATED"].c_str(), NULL};
    execve(_cgiPath.c_str(), const_cast<char **>(argv), _envp);
    close(rd[0]);
    exit(0);
  } else {
    close(fd[1]);
    waitpid(pid, &status, 0);
    while (read(fd[0], buf, 1024) > 0) {
      tmp += buf;
      memset(buf, 0, 1024);
    }
    _res = tmp;
    close(fd[0]);
  }
}
