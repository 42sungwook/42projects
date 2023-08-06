#ifndef POST_HPP
#define POST_HPP

#include "Method.hpp"

class Post : public Method {
 private:
 public:
  Post();
  ~Post();

  void process(Request &request, Response &response);
};

#endif
