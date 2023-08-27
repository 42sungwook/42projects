#ifndef POST_HPP
#define POST_HPP

#include "Method.hpp"

class Post : public Method {
 private:
  bool isCgi(const std::string &fullUri, Request &request);

 public:
  Post();
  ~Post();

  void process(Request &request, Response &response);
  std::string generateRandomString();
  void createResource(Response &response, std::string &fileName,
                      std::string &fullUri);
  void appendResource(const std::string &fileName, const Request &request);
  void coverResource(const std::string &fileName, const Request &request);
};

#endif
