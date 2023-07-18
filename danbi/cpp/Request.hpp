#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <map>

enum METHOD { GET, POST, DELETE };
enum PROCESS { CGI, NORMAL };

class Request {
  private:
    std::string _msg;
    std::map<std::string, std::string> _header;
    std::string _body;
    int _error;

  public:
    Request();
    ~Request();
    void parsing(std::string tmp);
    const std::string getMessage() const;
    const int &getError() const;
    enum PROCESS getProcess();
    enum METHOD getMethod();
};

#endif