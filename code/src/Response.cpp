#include "../includes/Response.hpp"

Response::Response(std::string result)
    : _header(), _body(), _statusLine(), _result(result) {}

Response::~Response() {}

void Response::convertCGI(std::string cgiResult) {
  // TODO Content-Type만 무조건 해야 함
  // 따라서 status line이나 Content-Length는 없으면 우리가 추가
  _result = cgiResult;
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
