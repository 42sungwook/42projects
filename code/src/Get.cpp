#include "../includes/Get.hpp"

Get::Get() {}

Get::~Get() {}

void Get::makeBody(Request &request, Response &response) {
  std::fstream file(_path.c_str());
  if (file.is_open()) {
    std::stringstream buffer;

    buffer << file.rdbuf();
    if (buffer.good() == false) {
      throw ErrorException(500);
      return;
    }
    _body = buffer.str();
    file.close();
  } else {
    throw ErrorException(404);
  }
  return;
}

void Get::makeStatusLine(Request &request, Response &response) {
  _statusLine += "HTTP/1.1 ";
  _statusLine += std::to_string(request.getStatus());
  _statusLine += response.getStatusCode(request.getStatus());
  _statusLine += "\r\n";
  return;
}

void Get::makeHeader(Request &request, Response &response) {
  if (_body != "") {
    if (request.getHeaderByKey("Content-Type") == "")
      _header += "Content-Type: text/html\r\n";
    else {
      _header += "Content-Type: ";
      _header += request.getHeaderByKey("Content-Type");
      _header += "\r\n";
    }
    _header += "Content-Length: ";
    _header += std::to_string(_body.length());
    _header += "\r\n";
  }
  _header += "\r\n";
  return;
}

void Get::makeResponse(Request &request, Response &response) {
  makeStatusLine(request, response);
  makeHeader(request, response);
  makeBody(request, response);
  response.setResult(_statusLine, _header, _body);
}

void Get::process(Request &request, Response &response) {
  try {
    std::string fullUri = request.getHeaderByKey("RootDir");
    fullUri += request.getHeaderByKey("BasicURI");
    if (fullUri[(fullUri.size() - 1)] == '/') {
      if (request.getHeaderByKey("Index") != "") {
        std::stringstream ss(request.getHeaderByKey("Index"));
        std::string token;

        while (ss >> token) {
          std::ifstream temp(fullUri.substr().append(token).c_str());
          if (temp.is_open() == true) {
            _path = fullUri.substr().append(token).c_str();
            makeResponse(request, response);
            return;
          }
        }
      }
      std::ifstream tmp(fullUri.substr().append("index.html").c_str());
      if (tmp.is_open() == true) {
        _path = fullUri.substr().append("index.html").c_str();
        makeResponse(request, response);
        return;
      }
      if (request.getHeaderByKey("AutoIndex") == "on")
        response.directoryListing(fullUri);
      else {
        throw ErrorException(403);
      }
    } else {
      std::ifstream tempf(fullUri.c_str());
      if (tempf.is_open() == true) {
        _path = fullUri.c_str();
        makeResponse(request, response);
        return;
      } else
        throw ErrorException(404);
    }
    makeResponse(request, response);
  } catch (ErrorException &e) {
    response.setErrorRes(e.getErrorCode());
  }
}
