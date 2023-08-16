#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <sys/stat.h>

#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

enum METHOD { GET, POST, DELETE };
enum PROCESS { CGI, NORMAL };

class Request {
 private:
  std::string _rawContents;
  std::map<std::string, std::string> _header;
  std::string _body;
  std::string _host;
  std::string _autoindex;
  std::string _mime;
  int _status;
  bool _isFullReq;
  std::map<std::string, std::string> _mimeTypes;

  void parseUrl();

 public:
  Request();
  ~Request();
  void parsing();
  void setAutoindex(std::string &value);
  void clear();
  void addRawContents(const std::string &raw);
  int  setMime();
  void addHeader(std::string key, std::string value);
  const std::string getHost();
  const std::string getUri();
  const std::string getMessage() const;
  const std::string getBody() const;
  const int &getStatus() const;
  const std::string &getAutoindex() const;
  const std::string &getMime() const;
  enum PROCESS getProcess();
  std::string getMethod();
  bool isFullReq() const;

  // temp
  std::string getRawContents() const;
  const std::string &getHeaderByKey(std::string key);
  std::map<std::string, std::string> getHeaderMap() const;
};

#endif
