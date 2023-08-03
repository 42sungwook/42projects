#include "../includes/Request.hpp"

Request::Request() : _mime(OCTET), _status(0), _isFullReq(false) {}

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
        _mime = OCTET;
    }
  }
}

void Request::parsing() {
  if (_rawContents.find("\r\n\r\n") == std::string::npos) {
    return;
  }
  std::stringstream ss(_rawContents);
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
             _header["method"] != "DELETE") {
    _status = 405;
  } else {
    _host = _header["Host"];
  }
  while (std::getline(ss, line)) {
    if (ss.eof() == true)
      _body += line;
    else if (line != "")
      _body += line + "\n";
  }
  if (_header["method"] == "POST" &&
      static_cast<size_t>(std::stoi(_header["Content-Length"])) !=
          _body.size()) {
    return;
  }
  // 8KB is default maximum size of request, config로 수정
  if (_rawContents.size() - _body.size() >= 8192) {
    _status = 414;
  }
  _isFullReq = true;
}

void Request::setAutoindex(std::string &value) { _autoindex = value; }

void Request::clear() {
  _rawContents.clear();
  _header.clear();
  _body.clear();
  _host.clear();
  _autoindex.clear();
  _status = 0;
  _isFullReq = false;
}

void Request::addRawContents(const std::string &raw) { _rawContents += raw; }

void Request::addHeader(std::string key, std::string value) {
  _header[key] = value;
}

const std::string Request::getUri() { return _header["URI"]; }

const std::string Request::getHost() { return _host; }

const int &Request::getPort() { return _port; }

const std::string Request::getBody() const { return _body; }

const std::string Request::getMessage() const { return "temp"; }

const std::string &Request::getAutoindex() const { return _autoindex; }

enum PROCESS Request::getProcess() { return CGI; }

const int &Request::getStatus() const { return _status; }

enum MIME Request::getMime() const { return _mime; }

std::string Request::getMethod() { return _header["method"]; }

bool Request::isFullReq() const { return _isFullReq; }

std::string Request::getRawContents() const { return _rawContents; }
