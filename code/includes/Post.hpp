#ifndef POST_HPP
#define POST_HPP

#include "Method.hpp"

class Post : public Method {
 private:
  void makeStatusLine(Request &request, Response &response);
  void makeHeader(Request &request, Response &response);
  void makeBody(Request &request, Response &response);
  void makeResponse(Request &request, Response &response);

 public:
  Post();
  ~Post();

  void process(Request &request, Response &response);
};

#endif
