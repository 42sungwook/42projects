#include "../includes/Delete.hpp"

std::string Delete::makeStatusLine(Request &request, Response &response) {
  std::string uri = request.getUri();
  size_t pos = uri.find("/");
  if (pos != std::string::npos)
    _path = uri.substr(uri.find("/"));
  else
    _path = uri + "/index.html";
  std::fstream file(_path.c_str());
  if (file.good()) {
    file.close();
    remove(_path.c_str());
    response.setStatusLine("HTTP/1.1 204 OK");
  } else {
    response.setStatusLine("HTTP/1.1 404 Not Found");
    response.setHeader("Content-Type: application/json");
    response.setHeader("Content-Length: 35");
    response.setBody("{\r\n\"error\": \"Resource not found\"\r\n}");
  }
  return (response.getStatusLine());
}

void Delete::process(Request &request, Response &response) {
  _result = makeStatusLine(request, response);
  if (response.getBody().length() > 0) {
    _result += response.getHeader();
    _result += "\r\n";
    _result += response.getBody();
  }
}

Delete::Delete() {}

Delete::~Delete() {}
