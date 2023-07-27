#include "../includes/Response.hpp"

Response::Response(std::string result) : _result(result) {}

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
