#ifndef POST_HPP
#define POST_HPP

#include "IMethod.hpp"

class Post : public IMethod {
 private:
  std::string _result;
  std::string _path;

 public:
  Post();
  ~Post();
  Post(const Post &obj);
  Post &operator=(const Post &obj);

  void process(Request &request, Response &response);

  std::string makeStatusLine(Request &request, Response &response);
  std::string makeHeader(Request &request, Response &response);
  std::string makeBody(Request &request, Response &response);
};

#endif
