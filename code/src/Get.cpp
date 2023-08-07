#include "../includes/Get.hpp"

Get::Get() {}

Get::~Get() {}

void Get::makeBody(Request &request, Response &response, std::ifstream &file) {
  std::stringstream buffer;

  buffer << file.rdbuf();
  if (buffer.good() == false) {
    throw ErrorException(500);
    return;
  }
  _body = buffer.str();
  file.close();
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

void Get::makeResponse(Request &request, Response &response, std::ifstream &file) {
  makeBody(request, response, file);
  makeHeader(request, response);
  makeStatusLine(request, response);
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
            makeResponse(request, response, temp);
          }
          else
            temp.close();
            return;
          }
        }
      std::ifstream tmp(fullUri.substr().append("index.html").c_str());
      if (tmp.is_open() == true) {
        _path = fullUri.substr().append("index.html").c_str();
        makeResponse(request, response, tmp);
        return;
      }
      else
        tmp.close();
      if (request.getHeaderByKey("AutoIndex") == "on")
        response.directoryListing(fullUri);
      else
        throw ErrorException(403);
      }
      else {
      std::ifstream tempf(fullUri.c_str());
      if (tempf.is_open() == true) {
        _path = fullUri.c_str();
        makeResponse(request, response, tempf);
        return;
      } else
        throw ErrorException(404);
    }
  } catch (ErrorException &e) {
    response.setErrorRes(e.getErrorCode());
  }
}
