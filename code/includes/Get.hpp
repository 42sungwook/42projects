#ifndef GET_HPP
#define GET_HPP

#include "IMethod.hpp"

class Get : public IMethod {
 private:
  std::string _result;
  std::string _path;

 public:
  Get();
  ~Get();

  void process(Request &request, Response &response);

  std::string makeBody(Request &request, Response &response);
  std::string makeHeader(Request &request, Response &response);
  std::string makeStatusLine(Request &request, Response &response);
};

#endif
