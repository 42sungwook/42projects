#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <sys/stat.h>

#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "RootBlock.hpp"

enum METHOD { GET, POST, DELETE };
enum PROCESS { CGI, NORMAL };
enum MIME { DIRECTORY, HTML, CSS, JS, JPG, PNG, GIF, TXT, PDF, JSON, OCTET };

class Request {
 private:
  std::string _rawContents;
  std::map<std::string, std::string> _header;
  std::string _body;
  std::string _host;
  std::string _autoindex;
  enum MIME _mime;
  int _port;
  int _status;
  bool _isFullReq;

 private:
  void parseUrl();

 public:
  Request();
  ~Request();
  void parsing();
  void setAutoindex(std::string &value);
  void clear();
  void addRawContents(const std::string &raw);
  void addHeader(std::string key, std::string value);
  const std::string getHost();
  const int &getPort();
  const std::string getUri();
  const std::string getMessage() const;
  const std::string getBody() const;
  const int &getStatus() const;
  const std::string &getAutoindex() const;
  enum MIME getMime() const;
  enum PROCESS getProcess();
  std::string getMethod();
  bool isFullReq() const;

  // temp
  std::string getRawContents() const;
};

#endif
