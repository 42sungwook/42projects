#include "../includes/Post.hpp"

Post::Post() {}

Post::~Post() {}

std::string Post::generateRandomString() {
  static std::string charset =
      "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
  std::string result;
  std::srand(std::time(0));

  for (int i = 0; i < 32; ++i)
    result.push_back(charset[std::rand() % charset.size()]);
  return result;
}

void Post::process(Request &request, Response &response) {
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
            request.addHeader(
                "BasicURI",
                std::string(request.getHeaderByKey("BasicURI")).append(token));
            Cgi cgi;
            cgi.reqToEnvp(request.getHeaderMap());
            cgi.excute(request.getBody());
            response.convertCGI(cgi.getRes());
            return;
          }
        }
      }
      std::ifstream tmp(fullUri.substr().append("index.html").c_str());
      if (tmp.is_open() == true) {
        _path = fullUri.substr().append("index.html").c_str();
        request.addHeader("BasicURI",
                          std::string(request.getHeaderByKey("BasicURI"))
                              .append("index.html"));
        Cgi cgi;
        cgi.reqToEnvp(request.getHeaderMap());
        cgi.excute(request.getBody());
        response.convertCGI(cgi.getRes());
        return;
      }
      throw ErrorException(403);
    } else {
      std::string filename = fullUri.c_str();
      std::ifstream tempif(filename);
      while (tempif.is_open() == true) {
        tempif.close();
        filename = generateRandomString();
        tempif.open(filename);
      }
      std::ofstream tempof(filename);
      _path = filename;
      Cgi cgi;
      cgi.reqToEnvp(request.getHeaderMap());
      cgi.excute(request.getBody());
      response.convertCGI(cgi.getRes());
      return;
    }
  } catch (ErrorException &e) {
    response.setErrorRes(e.getErrorCode());
  }
}
