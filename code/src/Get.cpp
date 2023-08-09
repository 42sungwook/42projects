#include "../includes/Get.hpp"

Get::Get() {}

Get::~Get() {}

void Get::makeBody(/* Request &request,  */ Response &response,
                   std::ifstream &file) {
  std::stringstream buffer;

  buffer << file.rdbuf();
  if (buffer.good() == false) throw ErrorException(500);
  response.setBody(buffer.str());
  file.close();
  return;
}

void Get::makeHeader(Request &request, Response &response) {
  if (_body != "") {
    if (request.getHeaderByKey("Content-Type") == "")
      response.setHeaders("Content-Type", "text/html");
    else
      response.setHeaders("Content-Type",
                          request.getHeaderByKey("Content-Type"));
  }
  response.setHeaders("Content-Length", ftItos(_body.length()));
}

void Get::makeResponse(Request &request, Response &response,
                       std::ifstream &file) {
  makeBody(response, file);
  makeHeader(request, response);
  response.setStatusLine(request.getStatus());
  response.setResult();
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
            return;
          }
        }
      }
      std::ifstream tmp(fullUri.substr().append("index.html").c_str());
      if (tmp.is_open() == true) {
        _path = fullUri.substr().append("index.html").c_str();
        makeResponse(request, response, tmp);
        return;
      }
      if (request.getHeaderByKey("AutoIndex") == "on")
        response.directoryListing(fullUri);
      else
        throw ErrorException(403);
    } else {
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
