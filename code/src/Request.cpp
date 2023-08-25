#include "../includes/Request.hpp"

#include "../includes/ErrorException.hpp"

Request::Request()
	: _mime("text/html"),
	  _status(200),
	  _isFullHeader(false),
	  _isChunked(false),
	  _isFullReq(false),
	  _locList(NULL),
	  _locBlock(NULL) {
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
  if (pos == uri.npos) pos = 0;
  try {
	_header["RawURI"] = uri.substr(pos, uri.find('?', pos) - pos);
  } catch (const std::exception &e) {
	std::cerr << e.what() << '\n';
	std::cerr << "substr err" << std::endl;
  }
}

void Request::parsing(SPSBList *serverBlockList, LocationMap &locationMap) {
  if (_rawContents.find("\r\n\r\n") == std::string::npos) {
	return;
  }

  std::stringstream ss(_rawContents);
  std::string line;

  if (_isFullHeader == false) {
	if (_rawContents.size() - _rawContents.find("\r\n\r\n") + 3 >= 8192) {
	  _status = 414;
	  _isFullReq = true;
	  return;
	}
	std::getline(ss, line, '\r');
	std::stringstream lineStream(line);
	lineStream >> _header["Method"] >> _header["URI"] >> _header["protocol"];
	parseUrl();

	while (std::getline(ss, line, '\r') && line != "\n") {
	  size_t pos = line.find(":");
	  if (pos == line.npos) {
		_status = 400;
	  }
	  size_t valueStartPos = line.find_first_not_of(" ", pos + 1);
	  size_t keyStartPos = line.find_first_not_of("\n", 0);

	  _header[line.substr(keyStartPos, pos - keyStartPos)] =
		  line.substr(valueStartPos);
	}
	std::getline(ss, line);
	if (_header.find("Transfer-Encoding") != _header.end()) {
	  _isChunked = true;
	}
	if (_header.find("Host") == _header.end()) {
	  _status = 400;
	} else if (_header["Method"] != "GET" && _header["Method"] != "POST" &&
		_header["Method"] != "DELETE" && _header["Method"] != "PUT") {
	  _status = 405;

	} else {
	  _host = _header["Host"];
	}

	setLocBlock(serverBlockList, locationMap);
	setMime();

	if (_header["Method"] != "POST") _isFullReq = true;
	_isFullHeader = true;
  }

  if (_isFullHeader == true && _isFullReq == false) {
	if (_isChunked) {
	  setChunkedBody(ss);

	} else {
	  if ((size_t)ftStoi(_header["Content-Length"]) >=
		  _locBlock->getClientMaxBodySize()) {
		_status = 413;
		_isFullReq = true;
	  }

	  setBody(ss);
	}
	_rawContents.clear();
  }
}

void Request::setBody(std::stringstream &ss) {
  std::string line;

  while (std::getline(ss, line)) {
	_body += line;
	if (!ss.eof()) _body += '\n';
  }
  if (static_cast<size_t>(std::atoi(_header["Content-Length"].c_str())) !=
	  _body.size()) {
	return;
  }
  _isFullReq = true;
}

void Request::setChunkedBody(std::stringstream &ss) {
  if (_header["Transfer-Encoding"] != "chunked" ||
	  (_header["Method"] != "POST" && _header["Method"] != "PUT")) {
	_status = 405;
	return;
  }
  std::string line;
  // std::getline(ss, line);
  while (std::getline(ss, line)) {  // 한줄읽고
	int len = hexToDecimal(line.substr(
		0, line.size() - 1));  // 읽은것중 맨마지막 \r 빼고 hex로 변환
	std::cout << "chunked len: " << len << std::endl;
	if (line == "0\r") {  // 0이면 chunked 끝
	  _isFullReq = true;
	  _header.erase("Transfer-Encoding");
	  break;  // 탈출 ^0^
	}
	std::getline(ss, line, '\r');  // \r전까지읽어서 바디에 저장
	_body += line;
	std::getline(ss, line);  // \n 지워주기
	// if (!ss.eof()) _body += '\n';  // 얜 머지?
  }
}

// 같은 포트를 공유하는 가상 호스트 리스트
void Request::setLocBlock(SPSBList *serverBlockList, LocationMap &locationMap) {
  std::string requestURI = getHeaderByKey("RawURI");
  ServerBlock *sb = NULL;

  for (SPSBList::iterator it = serverBlockList->begin();
	   it != serverBlockList->end(); it++) {
	if (_host == (*it)->getServerName()) {
	  sb = *it;
	  break;
	}
  }
  if (sb == NULL) sb = *(serverBlockList->begin());

  // 요청 호스트와 일치하는 가상호스트가 있다면 그 가상호스트에 있는
  // 로케이션블락을 찾아옴, 해당되는 로케이션 블락이 없으면 서버블락
  // 받아옴
  if (locationMap.find(sb) == locationMap.end())
	_locBlock = sb;
  else {
	_locList = locationMap[sb];
	for (LocationList::iterator it = _locList->begin(); it != _locList->end();
		 it++) {
	  if (requestURI.find((*it)->getPath()) != requestURI.npos) {
		addHeader("CuttedURI",
				  requestURI.erase(1, (*it)->getPath().length() - 1));
		_locBlock = *it;
		break;
	  }
	}
  }
  addHeader("RootDir", _locBlock->getRoot());
  addHeader("AutoIndex", _locBlock->getAutoindex());
  addHeader("Index", _locBlock->getIndex());
  addHeader("Name", _locBlock->getServerName());
  addHeader("Port", ftItos(_locBlock->getListenPort()));
  addHeader("Cgi", _locBlock->getCgi());
  addHeader("Cgi_Redir", _locBlock->getCgiRedir());
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
  //_autoindex.clear();
  _mime = "text/html";
  _status = 200;
  _isFullReq = false;
  _isChunked = false;
  _isFullHeader = false;
}

void Request::addRawContents(const std::string &raw) { _rawContents += raw; }

void Request::setMime() {
  struct stat info;
  std::string fullUri = _locBlock->getRoot();
  fullUri += _header["CuttedURI"];
  size_t lastDotPos = fullUri.rfind('.');

  if (lastDotPos != std::string::npos) {
	std::string mime = fullUri.substr(lastDotPos + 1);
	if (_mimeTypes.find(mime) != _mimeTypes.end())
	  _mime = _mimeTypes[mime];
	else
	  _mime = _mimeTypes["else"];
  } else {
	if (stat(fullUri.c_str(), &info) != 0) {
	  if (fullUri.back() != '/') {
		std::string requestURI = _header["RawURI"].substr(0).append("/");
		for (LocationList::iterator it = _locList->begin();
			 it != _locList->end();
			 it++) {
		  if (requestURI.find((*it)->getPath()) != requestURI.npos) {
			addHeader("CuttedURI",
					  requestURI.erase(1, (*it)->getPath().length() - 1));
			_locBlock = *it;
			fullUri = _locBlock->getRoot() + _header["CuttedURI"];
			break;
		  }
		}
		if (stat(fullUri.c_str(), &info) == 0 && S_ISDIR(info.st_mode)) {
		  _mime = _mimeTypes["directory"];
		  return;
		}
	  }
	  if (_header["Method"] == "PUT")
		_status = 201;
	  else
		_status = 404;
	  return;
	} else if (S_ISDIR(info.st_mode)) {
	  _mime = _mimeTypes["directory"];
	} else
	  _mime = _mimeTypes["else"];
  }
}

void Request::addHeader(std::string key, std::string value) {
  _header[key] = value;
}

const std::string &Request::getUri() { return _header["URI"]; }

const std::string &Request::getHost() { return _host; }

const std::string &Request::getBody() const { return _body; }

ServerBlock *Request::getLocBlock() const { return _locBlock; }

const std::string &Request::getAutoindex() const { return _autoindex; }

enum PROCESS Request::getProcess() { return CGI; }

const int &Request::getStatus() const { return _status; }

const std::string &Request::getMime() const { return _mime; }

const std::string &Request::getMethod() { return _header["Method"]; }

bool Request::isFullReq() const { return _isFullReq; }

const std::string &Request::getRawContents() const { return _rawContents; }

// Warning : always check _header[key] exist
const std::string &Request::getHeaderByKey(std::string key) {
  return _header[key];
}

std::map<std::string, std::string> Request::getHeaderMap() const {
  return _header;
}
