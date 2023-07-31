#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <map>
#include <sstream>

#include "RootBlock.hpp"

enum METHOD { GET, POST, DELETE };
enum PROCESS { CGI, NORMAL };
enum MIME { DIRECTORY, HTML, CSS, JS, JPG, PNG, GIF, TXT, PDF, JSON };

class Request {
 private:
  std::map<std::string, std::string> _header;
  std::string _body;
  std::string _host;
  std::string _autoindex;
  enum MIME _mime;
  int _port;
  int _status;

 private:
  const int parseUrl();

 public:
  Request();
  ~Request();
  void parsing(const std::string &raw);
  void setAutoindex(std::string &value);
  const std::string getHost();
  const int &getPort();
  const std::string getUri();
  const std::string getMessage() const;
  const int &getStatus() const;
	const std::string &getAutoindex() const;
	enum MIME &getMime() const;
  enum PROCESS getProcess();
  enum METHOD getMethod();
};

#endif