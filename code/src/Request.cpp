#include "../includes/Request.hpp"

Request::Request() : _status(0) {}

Request::~Request() {}

void Request::parseUrl() {
  struct stat info;
  std::string uri = _header["URI"];
  size_t lastDotPos = uri.rfind('.');

  if (lastDotPos != std::string::npos) {
    std::string mime = uri.substr(lastDotPos + 1);
    _mime = static_cast<enum MIME>(
        (mime == "html") + (mime == "css") * 2 + (mime == "js") * 3 +
        (mime == "jpg") * 4 + (mime == "png") * 5 + (mime == "gif") * 6 +
        (mime == "txt") * 7 + (mime == "pdf") * 8 + (mime == "json") * 9);
    if (!_mime) {
      if (stat(uri.c_str(), &info) != 0)
        _status = 404;
      else if (S_ISDIR(info.st_mode))
        _mime = DIRECTORY;
      else
        _status = 415;
    }
  }
}

void Request::parsing(const std::string &raw) {
  std::stringstream ss(raw);
  std::string line;
  std::getline(ss, line, '\r');
  std::stringstream lineStream(line);
  lineStream >> _header["method"] >> _header["URI"] >> _header["protocol"];
  parseUrl();
  while (std::getline(ss, line, '\r') && line != "\n") {
    size_t pos = line.find(":");
    if (pos == line.npos) {
      _status = 400;
      break;
    }
    _header[line.substr(1, pos - 1)] = line.substr(pos + 1, line.length());
  }
  if (_header.find("Host") == _header.end()) {
    _status = 400;
  } else if (_header["method"] != "GET" && _header["method"] != "POST" &&
             _header["method"] != "DELETE" && parseUrl()) {
        _status = 405;
  } else {
    _host = _header["Host"];
  }
  while (std::getline(ss, line))
    if (ss.eof() == true)
      _body += line;
    else if (line != "")
      _body += line + "\n";
  // 8KB is default maximum size of request, config로 수정
  if (raw.size() - _body.size() >= 8192) {
    _status = 414;
  }
}

void Request::setAutoindex(std::string &value) { _autoindex = value; }

const std::string Request::getUri() { return _header["URI"]; }

const std::string Request::getHost() { return _host; }

const int &Request::getPort() { return _port; }

const std::string Request::getMessage() const { return "temp"; }

const std::string &Request::getAutoindex() const { return _autoindex; }

enum PROCESS Request::getProcess() { return CGI; }

const int &Request::getStatus() const { return _status; };

enum METHOD Request::getMethod() { return GET; };

const std::string Request::getValueByKey(std::string key) {
  if (_header.find(key) == _header.end())
    throw std::runtime_error("Not Exist key");
  return _header[key];
};
