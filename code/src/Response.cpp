#include "../includes/Response.hpp"

Response::Response(std::string result)
    : _result(result), _statusLine(), _header(), _body() {
  _mimeTypes[HTML] = "text/html";
  _mimeTypes[CSS] = "text/css";
  _mimeTypes[JS] = "text/javascript";
  _mimeTypes[JPG] = "image/jpeg";
  _mimeTypes[PNG] = "image/png";
  _mimeTypes[GIF] = "image/gif";
  _mimeTypes[TXT] = "text/plain";
  _mimeTypes[PDF] = "application/pdf";
  _mimeTypes[JSON] = "application/json";
  _mimeTypes[OCTET] = "application/octet-stream";
  _statusCodes[200] = "OK";
  _statusCodes[201] = "Created";
  _statusCodes[202] = "Accepted";
  _statusCodes[204] = "No Content";
  _statusCodes[300] = "Multiple Choice";
  _statusCodes[301] = "Moved Permanently";
  _statusCodes[303] = "See Other";
  _statusCodes[304] = "Not Modified";
  _statusCodes[307] = "Temporary Redirect";
  _statusCodes[400] = "Bad Request";
  _statusCodes[401] = "Unauthorized";
  _statusCodes[403] = "Forbidden";
  _statusCodes[404] = "Not Found";
  _statusCodes[405] = "Method Not Allowed";
  _statusCodes[406] = "Not Acceptable";
  _statusCodes[409] = "Conflict";
  _statusCodes[410] = "Gone";
  _statusCodes[412] = "Precondition Failed";
  _statusCodes[414] = "URI Too Long";
  _statusCodes[415] = "Unsupported Media Type";
  _statusCodes[500] = "Server Error";
}

Response::~Response() {}

void Response::convertCGI(std::string cgiResult) {
  std::stringstream ss(cgiResult);
  std::string line;

  while (std::getline(ss, line)) {
    if (line.find("Content-Type") != std::string::npos) {
      _header += line;
      _header += "\r\n";
    } else if (line.find("Status") != std::string::npos) {
      _statusLine += line;
      _statusLine += "\r\n";
    } else if (line.find("Content-Length") != std::string::npos) {
      _header += line;
      _header += "\r\n";
    } else if (!line.empty()) {
      _body += line;
	  // TODO 마지막 문장에 개행 없으면 개행 붙이지 않기
      _body += "\n";
    }
  }
  if (_statusLine == "") {
    _statusLine += "HTTP/1.1 200 OK";
    _statusLine += "\r\n";
  }
  if (_header.find("Content-Length") == std::string::npos) {
    _header += "Content-Length: ";
    _header += std::to_string(_body.length());
    _header += "\r\n";
  }
  _result += _statusLine;
  _result += _header;
  _result += "\r\n";
  _result += _body;
}

void Response::directoryListing(std::string path) {
  DIR *dir;
  struct dirent *ent;
  std::string body;
  std::string header;
  std::string statusLine;
  std::string result;

  if ((dir = opendir(path.c_str())) != NULL) {
    /* print all the files and directories within directory */
    while ((ent = readdir(dir)) != NULL) {
      body += "<a href=\"";
      body += ent->d_name;
      body += "\">";
      body += ent->d_name;
      body += "</a><br>";
    }
    closedir(dir);
  } else {
    /* could not open directory */
    return;
  }
  header += "Content-Type: text/html";
  header += "\r\n";
  header += "Content-Length: ";
  header += std::to_string(body.length());
  header += "\r\n";
  statusLine += "HTTP/1.1 200 OK";
  statusLine += "\r\n";
  result += statusLine;
  result += header;
  result += "\r\n";
  result += body;
  _result = result;
  // ToDo 확인필요
}

int Response::sendResponse(int clientSocket) {
  if (write(clientSocket, _result.c_str(), _result.length()) == -1) return (1);
  return (0);
}

void Response::setBody(std::string body) {
  _body += body;
  _body += "\r\n";
}

void Response::setHeader(std::string header) {
  _header += header;
  _header += "\r\n";
}

void Response::setStatusLine(std::string statusLine) {
  _statusLine += statusLine;
  _statusLine += "\r\n";
}

std::string Response::getBody() { return _body; }

std::string Response::getHeader() { return _header; }

std::string Response::getStatusLine() { return _statusLine; }

std::string Response::getStatusCode(int key) {
  if (_statusCodes.find(key) == _statusCodes.end())
    throw std::runtime_error("Invalid status code");
  return _statusCodes[key];
}
void Response::setErrorRes(int statusCode) {
  _header.append("HTTP/1.1 ");
  _header.append(std::to_string(statusCode));
  _header.append(" ");
  _header.append(getStatusCode(statusCode));
  _header += "\r\n";
  _header += "Content-Type: text/plain";
  _header += "\r\n";
  _body += getStatusCode(statusCode);
  _body += " : Error";
  _body += "\r\n";
  _header += "Content-Length: ";
  _header += std::to_string(_body.length());
  _header += "\r\n\r\n";
}
