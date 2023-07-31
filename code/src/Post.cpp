#include "../includes/Post.hpp"

Post::Post() {}

Post::~Post() {}

Post::Post(const Post &obj) { *this = obj; }

Post &Post::operator=(const Post &obj) {
  *this = obj;
  return (*this);
}

std::string Post::makeBody(Request &request, Response &response) {
  std::string uri = request.getUri();
  size_t pos = uri.find("/");
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

std::string Post::makeStatusLine(Request &request, Response &response) {
  response.setStatusLine("HTTP/1.1 200 OK");
}

std::string Post::makeHeader(Request &request, Response &response) {
  if (response.getBody() != "") {
    response.setHeader("Content-Type: text/html");
    response.setHeader("Content-Length: " +
                       std::to_string(response.getBody().length()));
    return (response.getHeader());
  }
}

void Post::process(Request &request, Response &response) {
  _result += "\r\n";
  _result += makeBody(request, response);
  _result.insert(0, makeHeader(request, response));
  _result.insert(0, makeStatusLine(request, response));
}
