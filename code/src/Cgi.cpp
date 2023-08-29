#include "../includes/Cgi.hpp"
 
Cgi::Cgi() {}

Cgi::~Cgi() {}

void Cgi::makeEnv(std::map<std::string, std::string> param)
{
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
  for (std::map<std::string, std::string>::iterator it = param.begin();
       it != param.end(); it++)
  {
    if (it->first.find("X-") != std::string::npos)
    {
      std::string key = "HTTP_";
      key += it->first;
      size_t pos = key.find("-");
      while (pos != std::string::npos)
      {
        key.replace(pos, 1, "_");
        pos = key.find("-");
      }
      ftToupper(key);
      _env[key] = it->second;
    }
  }
}

void Cgi::reqToEnvp(std::map<std::string, std::string> param)
{
  makeEnv(param);
  _envp = new char *[_env.size() + 1];
  int i = 0;
  for (std::map<std::string, std::string>::iterator it = _env.begin();
       it != _env.end(); it++)
  {
    _envp[i] = new char[it->first.size() + it->second.size() + 2];
    std::string tmp = it->first + "=" + it->second;
    std::copy(tmp.begin(), tmp.end(), _envp[i]);
    _envp[i][tmp.size()] = '\0';
    i++;
  }
  _envp[i] = NULL;
}

const std::string &Cgi::getRes() const { return _res; }

void Cgi::execute(const std::string& body, Kqueue &kq, int clientFd) {
  pid_t pid;
  int inpipe[2];
  int outpipe[2];
  (void)body;

  fcntl(inpipe[0], F_SETFL, O_NONBLOCK);
  fcntl(inpipe[1], F_SETFL, O_NONBLOCK);
  fcntl(outpipe[0], F_SETFL, O_NONBLOCK);
  fcntl(outpipe[1], F_SETFL, O_NONBLOCK);
  if (pipe(inpipe) < 0)
    throw ErrorException(500);
  else if (pipe(outpipe) < 0) {
    close(inpipe[0]);
    close(inpipe[1]);
    throw ErrorException(500);
  }
  else if ((pid = fork()) == -1) {
    close(inpipe[0]);
    close(inpipe[1]);
    close(outpipe[0]);
    close(outpipe[1]);
    throw ErrorException(500);
  }
  if (pid == 0) { // child process
    close(inpipe[1]);
    close(outpipe[0]);
    dup2(inpipe[0], 0);
    dup2(outpipe[1], 1);
    close(inpipe[0]);
    close(outpipe[1]);
    const char *argv[2] = {_env["PATH_TRANSLATED"].c_str(), NULL};
    execve(_env["PATH_TRANSLATED"].c_str(), const_cast<char **>(argv), _envp);
    std::cerr << "execve error" << std::endl;
    exit(1);
  }
  close(inpipe[0]);
  close(outpipe[1]);
  std::vector<int> *fdVec = new std::vector<int>;
  fdVec->push_back(clientFd);
  fdVec->push_back(pid);
  fdVec->push_back(inpipe[1]);
  fdVec->push_back(outpipe[0]);
  fdVec->push_back(0);
  
  kq.setFdGroup(inpipe[1], FD_CGI);
  kq.setFdGroup(outpipe[0], FD_CGI);
  kq.changeEvents(inpipe[1], EVFILT_WRITE, EV_ADD | EV_ENABLE, 0, 0, fdVec);

}

// std::string Cgi::mkTemp()
// {//   int fd[2];
//   std::string path;
//   char buffer[100];
//   pid_t childPid;
//   size_t len;

//   if (pipe(fd) < 0)
//    throw ErrorException(500);
//   childPid = fork();
//   if (childPid == 0)
//   {
//     close(fd[0]);
//     dup2(fd[1], 1);
//     close(fd[1]);
//     execve("/usr/bin/mktemp", NULL, NULL);
//     std::cerr << "execve error" << std::endl;
//     exit(1);
//   }
//   else if (childPid == -1)
//    throw ErrorException(500);
//   waitpid(-1, NULL, 0);
//   close(fd[1]);
//   len = read(fd[0], buffer, 100);
//   path.append(buffer, len);
//   close(fd[0]);
//   return path;
// }

// void Cgi::execute(const std::string &body, Kqueue &kq)
// {
//   pid_t pid;
//   int fileFd;

//   std::string path = mkTemp();
//   std::string path2 = mkTemp();
//   if (path.empty())
//     return;

//   pid = fork();
//   if (pid == 0)
//   {
//     fileFd = open(path.c_str(), O_CREAT | O_RDWR, 0777);
//     if (fileFd == -1)
//     {
//       std::cerr << "open error" << std::endl;
//       exit(1);
//     }
    // const char *bodyData = body.c_str();
    // ssize_t bodySize = body.size();
    // ssize_t bytesWritten = 0;
    // ssize_t totalBytesWritten = 0;
    // ssize_t chunk = 32768;

    // while (totalBytesWritten < bodySize)
    // {
    //   if (totalBytesWritten + chunk > bodySize)
    //     chunk = bodySize - totalBytesWritten;
    //   bytesWritten = write(fileFd, bodyData + totalBytesWritten, chunk);
    //   if (bytesWritten == -1)
    //   {
    //     std::cerr << "write error" << std::endl;
    //     close(fileFd);
    //     exit(1);
    //   }
    //   totalBytesWritten += bytesWritten;
    // }
//     close(fileFd);
//     fileFd = open(path.c_str(), O_RDONLY);
//     dup2(fileFd, 0);
//     close(fileFd);
//     fileFd = open(path2.c_str(), O_CREAT | O_WRONLY, 0777);
//     dup2(fileFd, 1);
//     close(fileFd);
//     const char *argv[2] = {_env["PATH_TRANSLATED"].c_str(), NULL};
//     execve(_env["PATH_TRANSLATED"].c_str(), const_cast<char **>(argv), _envp);
//     std::cerr << "execve error" << std::endl;
//     exit(1);
//   }
//   else if (pid == -1)
//    throw ErrorException(500);
//   waitpid(pid, NULL, 0);
//   remove(path.c_str());
//   fileFd = open(path2.c_str(), O_RDONLY);

//   kq.changeEvents(fileFd, EVFILT_READ, EV_ADD | EV_ENABLE, 0, 0, NULL); // TODO event
  
//   // static char buf[32768];
//   // int n;

//   // while (true)
//   // {
//   //   n = read(fileFd, buf, sizeof(buf) - 1);
//   //   if (n == 0)
//   //     break;
//   //   else if (n == -1)
//   //     continue;
//   //   else {
//   //     buf[n] = '\0';
//   //     _res.append(buf, n);
//   //   }
//   // }
//   close(fileFd);
//   remove(path2.c_str());
// }