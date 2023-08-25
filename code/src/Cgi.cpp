#include "../includes/Cgi.hpp"

Cgi::Cgi() {}

Cgi::~Cgi() {}

void Cgi::makeEnv(std::map<std::string, std::string> param) {
  _env["AUTH_TYPE"] = param["Authorization"];
  _env["CONTENT_LENGTH"] = param["Content-Length"];
  _env["CONTENT_TYPE"] = param["Content-Type"];
  _env["GATEWAY_INTERFACE"] = "CGI/1.1";
  _env["PATH_INFO"] = param["RawURI"];
  if (param["Cgi_Redir"] == "")
    _env["PATH_TRANSLATED"] = param["RootDir"] + param["CuttedURI"];
  else
    _env["PATH_TRANSLATED"] = param["Cgi_Redir"];
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
  int fd[2];
  //int status;
  //char buf[8092];
  std::string tmp;
  //size_t len;
	pid_t childPid;
	
  if (pipe(fd) < 0) {
    std::cerr << "pipe error" << std::endl;
    return;
  }
	childPid = fork();
	if (childPid == 0) {
			// 자식 프로세스에서 실행할 로직
			write(fd[1], body.c_str(), body.size());
			close(fd[1]);
			const char *argv[2] = {_env["PATH_TRANSLATED"].c_str(), NULL};
			execve(_env["PATH_TRANSLATED"].c_str(), const_cast<char **>(argv), _envp);
			std::cerr << "execve error" << std::endl;
			exit(1);
	} else if (childPid == -1) {
			std::cerr << "fork error" << std::endl;
			exit (1);
	}

    char buffer[8092];
    ssize_t bytesRead;

		close(fd[1]);
    int kq = kqueue();
    if (kq == -1) {
        std::cerr << "kqueue error" << std::endl;
        return ;
    }

    struct kevent kev[2];
    EV_SET(&kev[0], fd[0], EVFILT_READ, EV_ADD | EV_ONESHOT, 0, 0, NULL);

    int nev = kevent(kq, kev, 1, NULL, 0, NULL);
    if (nev == -1) {
        std::cerr << "kevent error" << std::endl;
        return ;
    }

    while (true) {
        int events = kevent(kq, NULL, 0, kev, 1, NULL);
        if (events == -1) {
            std::cerr << "kevent error" << std::endl;
            return ;
        }

        if (events > 0 && (kev[0].flags & EV_EOF)) {
            // EOF 이벤트가 발생하면 더 이상 읽을 데이터가 없음
            break ;
        }

        bytesRead = read(fd[0], buffer, sizeof(buffer));
        if (bytesRead <= 0) {
            break ; // 더 이상 읽을 데이터가 없음
        }

        _res.append(buffer, bytesRead);
				memset(buffer, 0, 8092);
    }
    close(fd[0]);
}

// void Cgi::setCGIPath(const std::string &cgiPath) { _cgiPath = cgiPath; }

// const std::string Cgi::getCGIPath() const { return _cgiPath; }