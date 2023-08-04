#include "../includes/Get.hpp"

Get::Get() {}

Get::~Get() {}

Get::Get(const Get &obj) { *this = obj; }

Get &Get::operator=(const Get &obj) {
  *this = obj;
  return (*this);
}

std::string Get::makeBody(Request &request, Response &response) {
  std::string uri = request.getUri();
  size_t pos = uri.find("/");
  // need uri check
  if (pos != std::string::npos)
    _path = uri.substr(uri.find("/"));
  else
    _path = uri + "/index.html";
  std::fstream file(_path.c_str());
  if (file.is_open()) {
    std::string line;
    while (std::getline(file, line)) {
      response.setBody(line);
      if (file.eof() == false) response.setBody("\n");
    }
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
}

void Get::process(Request &request, Response &response) {
  _result += "\r\n";
  _result += makeBody(request, response);
  _result.insert(0, makeHeader(request, response));
  _result.insert(0, makeStatusLine(request, response));
}
