#ifndef GET_HPP
#define GET_HPP

#include "ErrorException.hpp"
#include "Method.hpp"

class Get : public Method {
 private:
  void makeBody(Request &request, Response &response);
  void makeHeader(Request &request, Response &response);
  void makeStatusLine(Request &request, Response &response);
  void makeResponse(Request &request, Response &response);

 public:
  Get();
  ~Get();

  void process(Request &request, Response &response);
};

#endif
