#include "../includes/Response.hpp"

#include "../includes/Utils.hpp"

Response::Response() {
  _body = new char[200000000];
  _result = new char[200000000];
  memset(_body, 0, 200000000);
  memset(_result, 0, 200000000);
  _statusCodes[200] = " OK";
  _statusCodes[201] = " Created";
  _statusCodes[202] = " Accepted";
  _statusCodes[204] = " No Content";
  _statusCodes[300] = " Multiple Choice";
  _statusCodes[301] = " Moved Permanently";
  _statusCodes[303] = " See Other";
  _statusCodes[304] = " Not Modified";
  _statusCodes[307] = " Temporary Redirect";
  _statusCodes[400] = " Bad Request";
  _statusCodes[401] = " Unauthorized";
  _statusCodes[403] = " Forbidden";
  _statusCodes[404] = " Not Found";
  _statusCodes[405] = " Method Not Allowed";
  _statusCodes[406] = " Not Acceptable";
  _statusCodes[408] = " Request Timeout";
  _statusCodes[409] = " Conflict";
  _statusCodes[410] = " Gone";
  _statusCodes[412] = " Precondition Failed";
  _statusCodes[413] = " Request Entity Too Large";
  _statusCodes[414] = " URI Too Long";
  _statusCodes[415] = " Unsupported Media Type";
  _statusCodes[500] = " Server Error";
}

Response::~Response() {
  delete[] _body;
  delete[] _result;
}

void Response::convertCGI(const char *cgiResult) {
  std::stringstream ss(cgiResult);
  std::string line;

  _headers.clear();
  _statusLine.clear();
  while (std::getline(ss, line, '\r') && line != "\n") {
    if (line.find("HTTP/1.1") != std::string::npos) {
      _statusLine += line;
    } else {
      size_t pos = line.find(":");
      if (pos == line.npos) break;
      size_t valueStartPos = line.find_first_not_of(" ", pos + 1);
      size_t keyStartPos = line.find_first_not_of("\n", 0);
      _headers[line.substr(keyStartPos, pos - keyStartPos)] =
          line.substr(valueStartPos);
    }
  }
  std::getline(ss, line);
  while (std::getline(ss, line)) {
    strcat(_body, line.c_str());
    if (!ss.eof()) strcat(_body, "\n");
  }

  if (_statusLine == "") {
    if (_headers.find("Status") != _headers.end()) {
      _statusLine += "HTTP/1.1 ";
      _statusLine += _headers["Status"];
      _headers.erase("Status");
    } else {
      setStatusLine(200);
    }
  }
  if (_headers.find("Content-Length") == _headers.end()) {
    setHeaders("Content-Length", ftItos(strlen(_body)));
  }
  setResult();
}

void Response::directoryListing(std::string path) {
  DIR *dir;
  struct dirent *ent;

  if ((dir = opendir(path.c_str())) != NULL) {
    /* print all the files and directories within directory */
    while ((ent = readdir(dir)) != NULL) {
      strcat(_body, "<a href=\"");
      strcat(_body, ent->d_name);
      if (ent->d_type == DT_DIR)
        strcat(_body, "/\">");
      else if (std::string(&ent->d_name[ent->d_namlen - 5]) != ".html")
        strcat(_body, "\" download>");
      else
        strcat(_body, "\">");
      strcat(_body, ent->d_name);
      strcat(_body, "</a><br>");
    }
    closedir(dir);
  } else {
    std::cout << "directory error : " << path.c_str() << std::endl;
    /* could not open directory */
    return;
  }
  _headers["Content-Type"] = "text/html";
  _headers["Content-Length"] = ftItos(strlen(_body));
  setStatusLine(200);
  setResult();
}

int Response::sendResponse(int clientSocket) {
  const char *dataToSend = _result;         // 시작 위치
  ssize_t remainingData = strlen(_result);  // 남은 데이터의 크기
  ssize_t chunk = 32768;

  std::cout << "status line: " << _statusLine << std::endl;
  while (remainingData > 0) {
    if (remainingData < chunk) chunk = remainingData;
    ssize_t bytesWritten = write(clientSocket, dataToSend, chunk);

    if (bytesWritten == -1) {
      continue;
    }
    dataToSend += bytesWritten;
    remainingData -= bytesWritten;
  }

  return 0;
}

const char *Response::getBody() const { return _body; }

void Response::setRedirectRes(int statusCode) {
  std::string location = _headers["Location"];
  _statusLine.clear();
  _headers.clear();
  memset(_body, 0, 200000000);

  _statusLine += "HTTP/1.1 ";
  _statusLine += ftItos(statusCode).c_str();
  _statusLine += _statusCodes[statusCode];
  _headers["Content-Type"] = "text/html";
  _headers["Location"] = location;
  strcat(_body, "<html>\n<head><title>");
  strcat(_body, ftItos(statusCode).c_str());
  strcat(_body, _statusCodes[statusCode].c_str());
  strcat(_body, "</title></head>\n<body>\n<center><h1>");
  strcat(_body, ftItos(statusCode).c_str());
  strcat(_body, _statusCodes[statusCode].c_str());
  strcat(
      _body,
      "</h1></center>\n<hr><center>webserver/1.0.0</center>\n</body>\n</html>");
  _headers["Content-Length"] = ftItos(strlen(_body));
  setResult();
}

void Response::setErrorRes(int statusCode) {
  std::ifstream tmp("./error.html");
  std::stringstream ss;

  _statusLine.clear();
  _headers.clear();
  memset(_body, 0, 200000000);

  _statusLine += "HTTP/1.1 ";
  _statusLine += ftItos(statusCode);
  _statusLine += _statusCodes[statusCode];
  _headers["Content-Type"] = "text/html";
  if (tmp.is_open() == false) {
    std::cout << "handle error 500" << std::endl;
    _headers["Content-Type"] = "text/plain";
    statusCode = 500;
  }
  if (tmp.is_open()) {
    ss << tmp.rdbuf();
    strcat(_body, ss.str().c_str());
  } else {
    strcat(_body, _statusCodes[statusCode].c_str());
    strcat(_body, ": Error");
  }
  if (statusCode == 408) {
    _headers["Connection"] = "close";
  }
  _headers["Content-Length"] = ftItos(strlen(_body));
  setResult();
}

bool Response::isInHeader(const std::string &key) {
  if (_headers.find(key) == _headers.end()) return false;
  return true;
}

void Response::setResult() {
  strcat(_result, _statusLine.c_str());
  strcat(_result, "\r\n");

  std::map<std::string, std::string>::iterator it;
  for (it = _headers.begin(); _headers.end() != it; it++) {
    strcat(_result, it->first.c_str());
    strcat(_result, ": ");
    strcat(_result, it->second.c_str());
    strcat(_result, "\r\n");
  }
  strcat(_result, "\r\n");
  strcat(_result, _body);
}

void Response::setStatusLine(int code) {
  _statusLine += "HTTP/1.1 ";
  _statusLine += ftItos(code);
  _statusLine += _statusCodes[code];
}
// std::string getFileExtension(const std::string &fileName) {
//   size_t dotPos = fileName.rfind('.');
//   if (dotPos == std::string::npos) return "";
//   return fileName.substr(dotPos + 1);
// }

void Response::setHeaders(const std::string &key, const std::string &value) {
  // std::string contentType = "text/html";  // default

  // if (ext == "css") {
  //   std::cout << "css file" << std::endl;
  //   contentType = "text/css";
  // }
  // if (ext == "js") {
  //    << "js file" << std::endl;
  //   contentType = "text/javascript";
  // }
  _headers[key] = value;
}

void Response::setBody(const char *body) { strcat(_body, body); }
