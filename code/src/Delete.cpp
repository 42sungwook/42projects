#include "../includes/Delete.hpp"

void Delete::detaultErrorPage() {
  _statusLine = "HTTP/1.1 404 Not Found\r\n";
  _header = "Content-Type: application/json\r\n";
  _header += "Content-Length: 35\r\n";
  _header += "\r\n";
  _body = "{\r\n\"error\": \"Resource not found\"\r\n}";
}

void Delete::deleteDenied() {
  _statusLine = "HTTP/1.1 403 Forbidden\r\n";
  _header = "Content-Type: application/json\r\n";
  _header += "Content-Length: 26\r\n";
  _header += "\r\n";
  _body = "{\r\n\"error\": \"Forbidden\"\r\n}";
}

void Delete::makeStatusLine(Request &request, Response &response) {
  std::string fullUri = request.getHeaderByKey("RootDir");
  fullUri += request.getHeaderByKey("BasicURI");
  if (fullUri[(fullUri.size() - 1)] == '/') {
    if (request.getHeaderByKey("Index") != "") {
      std::stringstream ss(request.getHeaderByKey("Index"));
      std::string token;

      while (ss >> token) {
        std::ifstream temp(fullUri.substr().append(token).c_str());
        if (temp.is_open() == true) {
          if (remove(fullUri.substr().append(token).c_str()) == 0) {
            _statusLine = "HTTP/1.1 204 OK\r\n";
            return;
          } else {
            deleteDenied();
            return;
          }
        }
      }
    }
    std::ifstream tmp(fullUri.substr().append("index.html").c_str());
    if (tmp.is_open() == true) {
      remove(fullUri.substr().append("index.html").c_str());
      _statusLine = "HTTP/1.1 204 OK\r\n";
      return;
    } else  // pure directory
      detaultErrorPage();
  } else {
    std::ifstream tempf(fullUri.substr().c_str());
    if (tempf.is_open() == true) {
      if (remove(fullUri.substr().c_str()) == 0) {
        _statusLine = "HTTP/1.1 204 OK\r\n";
        return;
      } else {
        deleteDenied();
        return;
      };
    } else  // file not found or can't open
      detaultErrorPage();
  }
}

void Delete::process(Request &request, Response &response) {
  makeStatusLine(request, response);
  response.setResult(_statusLine, _header, _body);
}

Delete::Delete() {}

Delete::~Delete() {}
