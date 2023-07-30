#include "../includes/Response.hpp"

Response::Response(std::string result)
    : _header(), _body(), _statusLine(), _result(result) {
  _mimeTypes[HTML] = "text/html";
  _mimeTypes[CSS] = "text/css";
  _mimeTypes[JS] = "text/javascript";
  _mimeTypes[JPG] = "image/jpeg";
  _mimeTypes[PNG] = "image/png";
  _mimeTypes[GIF] = "image/gif";
  _mimeTypes[TXT] = "text/plain";
  _mimeTypes[PDF] = "application/pdf";
  _mimeTypes[JSON] = "application/json";
}

Response::~Response() {}

void Response::convertCGI(std::string cgiResult) {
  // TODO Content-Type만 무조건 해야 함
  // 따라서 status line이나 Content-Length는 없으면 우리가 추가
  _result = cgiResult;
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
