#include "../includes/Get.hpp"

Get::Get() {}

Get::~Get() {}

std::string Get::makeBody(Request &request, Response &response) {
  std::fstream file(_path.c_str());
  if (file.is_open()) {
    std::stringstream buffer;

    buffer << file.rdbuf();
    if (buffer.good() == false) {
      response.setStatusLine("HTTP/1.1 500 Internal Server Error");
      return (response.getBody());
    }
    response.setBody(buffer.str());
    file.close();
  } else {
    response.setStatusLine("HTTP/1.1 404 Not Found");
  }
  return (response.getBody());
}

std::string Get::makeStatusLine(Request &request, Response &response) {
  std::string line;

  line += "HTTP/1.1 ";
  line += request.getStatus();
  line += response.getStatusCode(request.getStatus());
  return line;
}

std::string Get::makeHeader(Request &request, Response &response) {
  if (response.getBody() != "") {
    if (request.getHeaderByKey("Content-Type") == "")
      response.setHeader("Content-Type: text/html");
    else
      response.setHeader(std::string("Content-Type: ")
                             .append(request.getHeaderByKey("Content-Type")));
    response.setHeader(
        std::string("Content-Length: ")
            .append(std::to_string(response.getBody().length())));
    return (response.getHeader());
  }
  return "";
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
            return;
          }
        }
      }
      std::ifstream tmp(fullUri.substr().append("index.html").c_str());
      if (tmp.is_open() == true) {
        return;
      }
      if (request.getHeaderByKey("AutoIndex") == "on")
        response.directoryListing(fullUri);
      else {
        throw std::runtime_error("403");
      }
    } else {  // 파일일 경우
      std::ifstream tempf(fullUri.substr().c_str());
      if (tempf.is_open() == true) {
        // if (cgi) -> cgi로 함
        return;
      } else
        throw std::runtime_error("404");
    }
    // 내일 exception 처리하기~ 오늘은 수고했어요 ㅎㅎ 난 집갈래 ^^;
    _result += "\r\n";
    _result += makeBody(request, response);
    _result.insert(0, makeHeader(request, response));
    _result.insert(0, makeStatusLine(request, response));
  } catch (std::exception &e) {
    response.setErrorRes(std::atoi(e.what()));
  }
}
