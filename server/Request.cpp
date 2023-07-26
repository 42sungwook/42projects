#include "Request.hpp"

Request::Request() {}

Request::~Request() {}

void Request::parsing(const std::string& raw) {
  std::stringstream ss(raw);
  std::string line;
  std::getline(ss, line, '\r');
  std::stringstream lineStream(line);
  lineStream >> _header["method"] >> _header["URI"] >> _header["protocol"];
  while (std::getline(ss, line, '\r') && line != "\n") {
    int pos = line.find(":");
    if (pos == line.npos) {
      _error = 400;
      break;
    }
    _header[line.substr(1, pos - 1)] = line.substr(pos + 1, line.length());
  }
  if (_header["method"] != "GET" && _header["method"] != "POST" &&
      _header["method"] != "DELETE") {
    _error = 405;
  }
  while (std::getline(ss, line))
    if (ss.eof() == true)
      _body += line;
    else if (line != "")
      _body += line + "\n";
  // 8KB is default maximum size of request, config로 수정
  if (raw.size() - _body.size() >= 8192) {
    _error = 414;
  }
}

const std::string Request::getMessage() const {};

enum PROCESS Request::checkProcess() {
  if (_header["URI"].find(".php") != _header["URI"].npos ||
      _header["URI"].find(".py") != _header["URI"].npos ||
      _header["URI"].find(".cgi") != _header["URI"].npos ||
      _header["URI"].find(".pl") != _header["URI"].npos)
    return CGI;
  else
    return NORMAL;
};

const int& Request::getError() const { return _error; }

enum METHOD Request::getMethod(){};