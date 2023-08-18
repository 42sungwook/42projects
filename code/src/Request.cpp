#include "../includes/Request.hpp"

Request::Request() : _mime("text/html"), _status(200), _isFullReq(false) {
  _mimeTypes["html"] = "text/html";
  _mimeTypes["css"] = "text/css";
  _mimeTypes["js"] = "text/javascript";
  _mimeTypes["jpg"] = "image/jpeg";
  _mimeTypes["png"] = "image/png";
  _mimeTypes["gif"] = "image/gif";
  _mimeTypes["txt"] = "text/plain";
  _mimeTypes["pdf"] = "application/pdf";
  _mimeTypes["json"] = "application/json";
  _mimeTypes["ttf"] = "font/ttf";
  _mimeTypes["woff"] = "font/woff";
  _mimeTypes["woff2"] = "font/woff2";
  _mimeTypes["otf"] = "font/otf";
  _mimeTypes["else"] = "application/octet-stream";
  _mimeTypes["directory"] = "directory";
}

Request::~Request() {}

void Request::parseUrl() {
  std::string uri = _header["URI"];
  size_t pos = uri.find("://");

  if (pos == uri.npos)
    pos = 0;
  else
    pos += 3;
  pos = uri.find('/', pos);
  _header["BasicURI"] = uri.substr(pos, uri.find('?', pos) - pos);
}

void Request::parsing(SPSBList *serverBlockList, LocationMap &locationMap) {
  if (_rawContents.find("\r\n\r\n") == std::string::npos) {
    return;
  }
  std::stringstream ss(_rawContents);
  std::string line;
  std::getline(ss, line, '\r');
  std::stringstream lineStream(line);
  lineStream >> _header["Method"] >> _header["URI"] >> _header["protocol"];
  parseUrl();
  while (std::getline(ss, line, '\r') && line != "\n") {
    size_t pos = line.find(":");
    if (pos == line.npos) {
      _status = 400;
      break;
    }
    size_t valueStartPos = line.find_first_not_of(" ", pos + 1);
    size_t keyStartPos = line.find_first_not_of("\n", 0);
    _header[line.substr(keyStartPos, pos - keyStartPos)] =
        line.substr(valueStartPos);
  }
  if (_header.find("Host") == _header.end()) {
    _status = 400;
  } else if (_header["Method"] != "GET" && _header["Method"] != "POST" &&
             _header["Method"] != "DELETE") {
    _status = 405;
  } else {
    _host = _header["Host"];
  }

  if (_status == 200) {
    setLocBlock(serverBlockList, locationMap);
  }

  setMime();  // 셋마임 위치 정하기

  std::getline(ss, line);
  while (std::getline(ss, line)) {
    _body += line;
    if (!ss.eof()) _body += '\n';
  }
  // if (_header["Method"] == "POST" &&
  //     static_cast<size_t>(std::atoi(_header["Content-Length"].c_str())) !=
  //         _body.size()) {
  //   _status = 400;
  // }

  if (_body.size() >= _locBlock->getClientMaxBodySize()) _status = 413;
  if (_rawContents.size() - _body.size() >= 8192) {
    _status = 414;
  }
  _isFullReq = true;
}

void Request::setLocBlock(SPSBList *serverBlockList, LocationMap &locationMap) {
  std::string requestURI = getHeaderByKey("BasicURI");
  ServerBlock *sb = NULL;

  for (SPSBList::iterator it = serverBlockList->begin();
       it != serverBlockList->end(); it++) {
    if (_host == (*it)->getServerName()) {
      sb = *it;
      break;
    }
  }
  if (sb == NULL) sb = *(serverBlockList->begin());

  if (locationMap.find(sb) == locationMap.end())
    _locBlock = sb;
  else {
    LocationList *locList = locationMap[sb];
    for (LocationList::iterator it = locList->begin(); it != locList->end();
         it++) {
      if (requestURI.find((*it)->getPath()) != requestURI.npos) {
        addHeader("BasicURI",
                  requestURI.erase(1, (*it)->getPath().length() - 1));
        _locBlock = *it;
        break;
      }
    }
  }
};

void Request::setAutoindex(std::string &value) { _autoindex = value; }

void Request::clear() {
  _rawContents.clear();
  addRawContents("");
  std::string clientIp = _header["ClientIP"];
  _header.clear();
  _header["ClientIP"] = clientIp;
  _body.clear();
  _host.clear();
  // _autoindex.clear();
  _mime = "text/html";
  _status = 200;
  _isFullReq = false;
}

void Request::addRawContents(const std::string &raw) { _rawContents += raw; }

int Request::setMime() {
  struct stat info;
  std::string fullUri = _locBlock->getRoot();
  fullUri += _header["BasicURI"];
  size_t lastDotPos = fullUri.rfind('.');

  if (lastDotPos != std::string::npos) {
    std::string mime = fullUri.substr(lastDotPos + 1);
    if (_mimeTypes.find(mime) != _mimeTypes.end())
      _mime = _mimeTypes[mime];
    else
      _mime = _mimeTypes["else"];
  } else {
    if (stat(fullUri.c_str(), &info) != 0) {
      _status = 404;
      return (EXIT_FAILURE);
    } else if (S_ISDIR(info.st_mode))
      _mime = _mimeTypes["directory"];
    else
      _mime = _mimeTypes["else"];
  }
  return (EXIT_SUCCESS);
}

void Request::addHeader(std::string key, std::string value) {
  _header[key] = value;
}

const std::string Request::getUri() { return _header["URI"]; }

const std::string Request::getHost() { return _host; }

const std::string Request::getBody() const { return _body; }

const std::string Request::getMessage() const { return "temp"; }  // <<<<

const std::string &Request::getAutoindex() const { return _autoindex; }

enum PROCESS Request::getProcess() { return CGI; }

const int &Request::getStatus() const { return _status; }

const std::string &Request::getMime() const { return _mime; }

std::string Request::getMethod() { return _header["Method"]; }

bool Request::isFullReq() const { return _isFullReq; }

std::string Request::getRawContents() const { return _rawContents; }

// Warning : always check _header[key] exist
const std::string &Request::getHeaderByKey(std::string key) {
  return _header[key];
}

std::map<std::string, std::string> Request::getHeaderMap() const {
  return _header;
}
