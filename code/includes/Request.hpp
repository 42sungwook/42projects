#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <sys/stat.h>

#include <cstdlib>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include "../includes/LocationBlock.hpp"
#include "ConfigParser.hpp"
#include "Utils.hpp"

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
  bool _isFullHeader;
  bool _isFullReq;
  std::map<std::string, std::string> _mimeTypes;
  ServerBlock *_locBlock;

  void parseUrl();

 public:
  Request();
  ~Request();
  void parsing(SPSBList *serverBlockList, LocationMap &locationMap);
  int setMime();
  void setLocBlock(SPSBList *serverBlockList, LocationMap &locationMap);
  void setAutoindex(std::string &value);
  void addRawContents(const std::string &raw);
  void addHeader(std::string key, std::string value);
  void clear();
  const std::string &getHost();
  const std::string &getUri();
  const std::string &getBody() const;
  const int &getStatus() const;
  ServerBlock *getLocBlock() const;
  const std::string &getAutoindex() const;
  const std::string &getMime() const;
  enum PROCESS getProcess();
  const std::string &getMethod();
  bool isFullReq() const;
  const std::string &getRawContents() const;
  const std::string &getHeaderByKey(std::string key);
  std::map<std::string, std::string> getHeaderMap() const;
  void setBody(std::stringstream &ss);
  void setChunkedBody(std::stringstream &ss);
};

#endif
