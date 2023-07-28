#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <iostream>
#include <map>
#include <string>

void excute(std::string body, char **ev) {
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
    write(0, body.c_str(), body.size() + 1);
    char *command_path = "/bin/cat";
    char *args[] = {command_path, NULL};
    execve(command_path, args, ev);
    exit(0);
  } else {
    close(fd[1]);
    waitpid(pid, &status, 0);
    while (read(fd[0], buf, 1024) > 0) {
      tmp += buf;
      memset(buf, 0, 1024);
    }
    close(fd[0]);
    std::cout << tmp << std::endl;
  }
}

int main(int ac, char **av, char **ev) { excute("Hello World", ev); }

int stoi(std::string str) {
  int ret = 0;
  bool neg = false;

  if (str[0] == '-') {
    neg = true;
    str = str.substr(1, str.size() - 1);
  }
  for (int i = 0; i < str.size() && str[i] >= '0' && str[i] <= '9'; i++) {
    ret *= 10;
    ret += str[i] - '0';
  }
  if (neg) ret = -ret;
  return ret;
}

std::string itos(int num) {
  std::string ret;
  bool neg = false;

  if (num < 0) {
    neg = true;
    num = -num;
  }
  while (num) {
    ret += num % 10 + '0';
    num /= 10;
  }
  std::reverse(ret.begin(), ret.end());
  if (neg) ret = "-" + ret;
  return ret;
}