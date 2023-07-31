#include "../includes/Request.hpp"

Request::Request() : _status(0) {}

Request::~Request() {}

void Request::parseUrl() {
  std::string uri = _header["URI"];
  size_t lastDotPos = uri.rfind('.');

  if (lastDotPos != std::string::npos) {
    std::string mime = uri.substr(lastDotPos + 1);
    // enum mime이랑 비교 후 저장
  }
}

void Request::parsing(const std::string &raw) {
  std::stringstream ss(raw);
  std::string line;
  std::getline(ss, line, '\r');
  std::stringstream lineStream(line);
  lineStream >> _header["method"] >> _header["URI"] >> _header["protocol"];
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
  }
  else if (_header["method"] != "GET" && _header["method"] != "POST" &&
      _header["method"] != "DELETE") {
    _status = 405;
  }
  else {
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

const std::string Request::getUri() { return _header["URI"]; };

const std::string Request::getHost() { return _host; };

const int &Request::getPort() { return _port; };

const std::string Request::getMessage() const { return "temp"; };

enum PROCESS Request::getProcess() { return CGI; };

const int &Request::getStatus() const { return _status; }

enum METHOD Request::getMethod() { return GET; };