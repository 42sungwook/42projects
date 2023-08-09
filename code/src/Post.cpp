#include "../includes/Post.hpp"

Post::Post() {}

Post::~Post() {}

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
      if (request.getHeaderByKey("AutoIndex") == "on")
        response.directoryListing(fullUri);
      else
        throw ErrorException(403);
    } else {
      std::ifstream tempf(fullUri.c_str());
      if (tempf.is_open() == true) {
        _path = fullUri.c_str();
        Cgi cgi;
        cgi.reqToEnvp(request.getHeaderMap());
        cgi.excute(request.getBody());
        response.convertCGI(cgi.getRes());
        return;
      } else
        throw ErrorException(404);
    }
  } catch (ErrorException &e) {
    response.setErrorRes(e.getErrorCode());
  }
}
